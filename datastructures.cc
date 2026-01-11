// Datastructures.cc

// TEST SUBMISSION
#include "datastructures.hh"

#include <random>
#include <algorithm>
#include <queue>
#include <set>
#include <functional>

std::minstd_rand rand_engine; // Reasonably quick pseudo-random generator

template <typename Type>
Type random_in_range(Type start, Type end)
{
    auto range = end-start;
    ++range;

    auto num = std::uniform_int_distribution<unsigned long int>(0, range-1)(rand_engine);

    return static_cast<Type>(start+num);
}

// Modify the code below to implement the functionality of the class.
// Also remove comments from the parameter names when you implement
// an operation (Commenting out parameter name prevents compiler from
// warning about unused parameters on operations you haven't yet implemented.)

Datastructures::Datastructures()
{
    // Write any initialization you need here

}

Datastructures::~Datastructures()
{
    // Write any cleanup you need here

}

// A operations

// Add a beacon with the given parameters. If a beacon with the given ID
// already exists, nothing is done and false is returned. Otherwise true
bool Datastructures::add_beacon(BeaconID id, const Name& name, Coord xy, Color color)
{
    if (beacons_.count(id) > 0) {
        return false;
    }

    beacons_[id] = {name, xy, color, NO_BEACON, {}};
    return true;
}

// Returns the number of beacons stored
int Datastructures::beacon_count()
{
    return beacons_.size();
}

// Removes all beacons
void Datastructures::clear_beacons()
{
    beacons_.clear();
}

// Returns IDs of all beacons stored
std::vector<BeaconID> Datastructures::all_beacons()
{
    std::vector<BeaconID> result;
    result.reserve(beacons_.size());

    for (auto& p : beacons_) {
        result.push_back(p.first);
    }

    return result;
}

// Returns the name of the beacon with the given ID
Name Datastructures::get_name(BeaconID id)
{
    if (!beacons_.count(id)) return NO_NAME;
    return beacons_[id].name;
}

// Returns the coordinates of the beacon with the given ID
Coord Datastructures::get_coordinates(BeaconID id)
{
    if (!beacons_.count(id)) return NO_COORD;
    return beacons_[id].xy;
}

// Returns the color of the beacon with the given ID
Color Datastructures::get_color(BeaconID id)
{
    if (!beacons_.count(id)) return NO_COLOR;
    return beacons_[id].color;
}

// Returns the IDs of all beacons sorted in alphabetical order by their names
std::vector<BeaconID> Datastructures::beacons_alphabetically()
{
    std::vector<std::pair<Name, BeaconID>> temp;

    for (auto& p : beacons_) {
        temp.push_back({p.second.name, p.first});
    }

    std::sort(temp.begin(), temp.end());

    std::vector<BeaconID> result;
    result.reserve(temp.size());
    for (auto& t : temp)
        result.push_back(t.second);

    return result;
}

// Helper function to calculate brightness
static int brightness(Color c)
{
    return c.r + c.g + c.b;
}

// Returns the IDs of all beacons sorted by increasing brightness
std::vector<BeaconID> Datastructures::beacons_brightness_increasing()
{
    std::vector<BeaconID> ids;
    ids.reserve(beacons_.size());

    for (auto& p : beacons_)
        ids.push_back(p.first);

    std::sort(ids.begin(), ids.end(),
        [&](auto& a, auto& b) {
            return brightness(beacons_[a].color) < brightness(beacons_[b].color);
        });

    return ids;
}

// Returns the ID of the beacon with the lowest brightness
BeaconID Datastructures::min_brightness()
{
    if (beacons_.empty()) return NO_BEACON;

    auto it = std::min_element(beacons_.begin(), beacons_.end(),
        [](auto& a, auto& b) {
            return brightness(a.second.color) < brightness(b.second.color);
        });

    return it->first;
}

// Returns the ID of the beacon with the highest brightness
BeaconID Datastructures::max_brightness()
{
    if (beacons_.empty()) return NO_BEACON;

    auto it = std::max_element(beacons_.begin(), beacons_.end(),
        [](auto& a, auto& b) {
            return brightness(a.second.color) < brightness(b.second.color);
        });

    return it->first;
}

// Returns beacons with the given name, or an empty vector if none exist. 
std::vector<BeaconID> Datastructures::find_beacons(Name const& name)
{
     std::vector<BeaconID> result;

    for (auto& p : beacons_) {
        if (p.second.name == name)
            result.push_back(p.first);
    }

    std::sort(result.begin(), result.end());
    return result;
}

// Changes the name of the beacon with the given ID. 
// If the beacon is not found, returns false, otherwise true.
bool Datastructures::change_beacon_name(BeaconID id, const Name& newname)
{
    if (!beacons_.count(id)) return false;

    beacons_[id].name = newname;
    return true;
}

/*
Adds a light beam from one beacon to another. A beacon can only send 
light to one other beacon. In the work, it is assumed that light beams 
cannot form loops (i.e. a beacon cannot directly or indirectly illuminate 
itself). If either of the beacons is not found or the source beacon is 
already sending light to another beacon, nothing is done and false is 
returned.* Otherwise true is returned.
*/
bool Datastructures::add_lightbeam(BeaconID sourceid, BeaconID targetid)
{
    if (!beacons_.count(sourceid) || !beacons_.count(targetid)) {
        return false;
    }

    Beacon& source = beacons_[sourceid];
    Beacon& target = beacons_[targetid];

    if (source.outgoing != NO_BEACON) {
        return false;
    }

    // Check for loops
    BeaconID current = targetid;
    while (current != NO_BEACON) {
        if (current == sourceid) {
            return false; // Loop detected
        }
        current = beacons_[current].outgoing;
    }

    source.outgoing = targetid;
    target.incoming.push_back(sourceid);
    return true;
}

/*
Returns the IDs of beacons that are transmitting their light directly 
to the beacon with the given ID, or a vector whose only element is 
NO_BEACON, if no beacon with the given ID is found. The return values 
should be sorted in ascending order of IDs. (The main program calls 
this in various places.)
*/
std::vector<BeaconID> Datastructures::get_lightsources(BeaconID id)
{
    if (!beacons_.count(id)) {
        return {NO_BEACON};
    }

    std::vector<BeaconID> sources = beacons_[id].incoming;
    std::sort(sources.begin(), sources.end());
    return sources;
}

/*
Returns a list of beacons to which the given beacon transmits light 
directly or indirectly. The return vector first stores the beacon itself, 
then the direct target beacon of that light, the target beacon’s target 
beacon, etc., as long as there are enough light rays. If there is no 
beacon with the given id, a vector is returned whose only element is 
NO_BEACON.
*/
std::vector<BeaconID> Datastructures::path_outbeam(BeaconID id)
{
    if (!beacons_.count(id)) {
        return {NO_BEACON};
    }

    std::vector<BeaconID> path;
    BeaconID current = id;

    while (current != NO_BEACON) {
        path.push_back(current);
        current = beacons_[current].outgoing;
    }

    return path;
}

// B operations

/*
Returns the longest possible chain of light rays that 
terminate at the given beacon. 
*/
std::vector<BeaconID> Datastructures::path_inbeam_longest(BeaconID id)
{
    if (!beacons_.count(id)) {
        return {NO_BEACON};
    }

    // Use DFS to find the longest path ending at this beacon
    std::vector<BeaconID> longest;
    
    std::function<std::vector<BeaconID>(BeaconID)> dfs = [&](BeaconID current) -> std::vector<BeaconID> {
        std::vector<BeaconID> currentPath = {current};
        
        // Check all beacons that point to this one
        const auto& incoming = beacons_[current].incoming;
        std::vector<BeaconID> longestFrom;
        
        for (const auto& source : incoming) {
            auto pathFrom = dfs(source);
            if (pathFrom.size() > longestFrom.size()) {
                longestFrom = pathFrom;
            }
        }
        
        // Append current beacon to the longest path from incoming beacons
        longestFrom.push_back(current);
        return longestFrom;
    };
    
    return dfs(id);
}

// Returns the total color of the beacon with the given ID
Color Datastructures::total_color(BeaconID id)
{
    if (!beacons_.count(id)) {
        return NO_COLOR;
    }

    const auto& beacon = beacons_[id];
    
    // Start with the beacon's own color
    int totalR = beacon.color.r;
    int totalG = beacon.color.g;
    int totalB = beacon.color.b;
    
    // Add colors from all incoming light beams
    int count = 1; // including the beacon itself
    for (const auto& sourceId : beacon.incoming) {
        const auto& sourceColor = total_color(sourceId);
        totalR += sourceColor.r;
        totalG += sourceColor.g;
        totalB += sourceColor.b;
        count++;
    }
    
    return {totalR / count, totalG / count, totalB / count};
}

// Adds a fibre (edge) between two crossing points with the given cost
bool Datastructures::add_fibre(Coord xpoint1, Coord xpoint2, Cost cost)
{
    // Cannot add fibre if both points are the same
    if (xpoint1 == xpoint2) {
        return false;
    }

    // Normalize so that smaller coordinate is always first
    if (xpoint2 < xpoint1) {
        std::swap(xpoint1, xpoint2);
    }

    // Check if fibre already exists
    if (fibres_.count(xpoint1) && fibres_[xpoint1].count(xpoint2)) {
        return false;
    }

    // Add fibre in both directions (undirected graph)
    fibres_[xpoint1][xpoint2] = cost;
    fibres_[xpoint2][xpoint1] = cost;
    
    return true;
}

// Returns all fiber endpoints in the data structure in 
// coordinate order
std::vector<Coord> Datastructures::all_xpoints()
{
    std::set<Coord> points;
    
    for (const auto& [coord, _] : fibres_) {
        points.insert(coord);
    }
    
    return std::vector<Coord>(points.begin(), points.end());
}

// Returns a list of coordinates to which fibers directly 
// go from the given coordinate, and the cost of the fiber 
// in question.
std::vector<std::pair<Coord, Cost>> Datastructures::get_fibres_from(Coord xpoint)
{
    std::vector<std::pair<Coord, Cost>> result;
    
    if (fibres_.count(xpoint)) {
        for (const auto& [target, cost] : fibres_[xpoint]) {
            result.push_back({target, cost});
        }
        // Sort by coordinate order
        std::sort(result.begin(), result.end());
    }
    
    return result;
}

// Returns all fibers stored as pairs of coordinates
std::vector<std::pair<Coord, Coord>> Datastructures::all_fibres()
{
    std::vector<std::pair<Coord, Coord>> result;
    std::set<std::pair<Coord, Coord>> seen;
    
    for (const auto& [from, targets] : fibres_) {
        for (const auto& [to, _] : targets) {
            // Store in normalized form (smaller first)
            auto normalized = std::make_pair(from, to);
            if (normalized.second < normalized.first) {
                std::swap(normalized.first, normalized.second);
            }
            
            // Only add each fibre once
            if (!seen.count(normalized)) {
                seen.insert(normalized);
                result.push_back(normalized);
            }
        }
    }
    
    return result;
}

// Removes the fibre between the two given coordinates
bool Datastructures::remove_fibre(Coord xpoint1, Coord xpoint2)
{
    if (xpoint1 == xpoint2) {
        return false;
    }

    // Normalize
    if (xpoint2 < xpoint1) {
        std::swap(xpoint1, xpoint2);
    }

    // Check if fibre exists
    if (!fibres_.count(xpoint1) || !fibres_[xpoint1].count(xpoint2)) {
        return false;
    }

    // Remove from both directions
    fibres_[xpoint1].erase(xpoint2);
    fibres_[xpoint2].erase(xpoint1);
    
    // Clean up empty entries
    if (fibres_[xpoint1].empty()) {
        fibres_.erase(xpoint1);
    }
    if (fibres_[xpoint2].empty()) {
        fibres_.erase(xpoint2);
    }
    
    return true;
}

// Removes all fibres
void Datastructures::clear_fibres()
{
    fibres_.clear();
}

// Returns any route between the two given points
std::vector<std::pair<Coord, Cost>> Datastructures::route_any(Coord fromxpoint, Coord toxpoint)
{
    // BFS to find any path from fromxpoint to toxpoint
    std::vector<std::pair<Coord, Cost>> result;
    
    if (!fibres_.count(fromxpoint)) {
        return result; // No fibres from starting point
    }

    auto coordToString = [](Coord c) {
        return std::to_string(c.x) + "," + std::to_string(c.y);
    };
    
    // BFS structures
    std::unordered_map<std::string, Coord> parent;
    std::unordered_map<std::string, Cost> distance;
    std::queue<Coord> bfs;
    
    std::string startKey = coordToString(fromxpoint);
    std::string endKey = coordToString(toxpoint);
    
    bfs.push(fromxpoint);
    distance[startKey] = 0;
    parent[startKey] = {NO_VALUE, NO_VALUE};
    
    // BFS loop
    while (!bfs.empty()) {
        Coord current = bfs.front();
        bfs.pop();
        
        std::string currentKey = coordToString(current);
        
        if (current == toxpoint) {
            // Reconstruct path
            Coord node = toxpoint;
            result.push_back({node, distance[coordToString(node)]});
            
            while (parent[coordToString(node)].x != NO_VALUE) {
                node = parent[coordToString(node)];
                result.push_back({node, distance[coordToString(node)]});
            }
            
            std::reverse(result.begin(), result.end());
            return result;
        }
        
        // Explore neighbors
        if (fibres_.count(current)) {
            for (const auto& [next, cost] : fibres_[current]) {
                std::string nextKey = coordToString(next);
                if (!distance.count(nextKey)) {
                    distance[nextKey] = distance[currentKey] + cost;
                    parent[nextKey] = current;
                    bfs.push(next);
                }
            }
        }
    }
    
    return result; 
}

// Returns a route between the two given points that passes through the fewest crossing points
std::vector<std::pair<Coord, Cost>> Datastructures::route_least_xpoints(Coord fromxpoint, Coord toxpoint)
{
    std::vector<std::pair<Coord, Cost>> result;
    
    // Check if starting point exists
    if (!fibres_.count(fromxpoint)) {
        return result;
    }
    
    // If start and end are the same
    if (fromxpoint == toxpoint) {
        result.push_back({fromxpoint, 0});
        return result;
    }
    
    // BFS to find shortest path in terms of number of crossing points
    std::unordered_map<Coord, Coord, CoordHash> parent;
    std::unordered_map<Coord, Cost, CoordHash> distance;
    std::queue<Coord> bfs;
    
    bfs.push(fromxpoint);
    distance[fromxpoint] = 0;
    parent[fromxpoint] = NO_COORD;
    
    bool found = false;
    
    while (!bfs.empty() && !found) {
        Coord current = bfs.front();
        bfs.pop();
        
        if (current == toxpoint) {
            found = true;
            break;
        }
        
        // Explore neighbors
        if (fibres_.count(current)) {
            for (const auto& [next, cost] : fibres_[current]) {
                if (!distance.count(next)) {
                    distance[next] = distance[current] + cost;
                    parent[next] = current;
                    bfs.push(next);
                }
            }
        }
    }
    
    // If no path found
    if (!found) {
        return result;
    }
    
    // Reconstruct path
    std::vector<std::pair<Coord, Cost>> path;
    Coord node = toxpoint;
    
    while (node != NO_COORD) {
        path.push_back({node, distance[node]});
        node = parent[node];
    }
    
    std::reverse(path.begin(), path.end());
    return path;
}

// Returns a route between the two given points that has the lowest total cost
std::vector<std::pair<Coord, Cost>> Datastructures::route_fastest(Coord fromxpoint, Coord toxpoint)
{
    std::vector<std::pair<Coord, Cost>> result;
    
    // Check if starting point exists
    if (!fibres_.count(fromxpoint)) {
        return result;
    }
    
    // If start and end are the same
    if (fromxpoint == toxpoint) {
        result.push_back({fromxpoint, 0});
        return result;
    }
    
    // Dijkstra's algorithm
    std::unordered_map<Coord, Cost, CoordHash> distance;
    std::unordered_map<Coord, Coord, CoordHash> parent;
    
    // Priority queue: (distance, coord)
    using PQElement = std::pair<Cost, Coord>;
    std::priority_queue<PQElement, std::vector<PQElement>, std::greater<PQElement>> pq;
    
    distance[fromxpoint] = 0;
    parent[fromxpoint] = NO_COORD;
    pq.push({0, fromxpoint});
    
    bool found = false;
    
    while (!pq.empty()) {
        auto [currentDist, current] = pq.top();
        pq.pop();
        
        // If already processed this node with a better distance, skip
        if (distance.count(current) && currentDist > distance[current]) {
            continue;
        }
        
        if (current == toxpoint) {
            found = true;
            break;
        }
        
        // Explore neighbors
        if (fibres_.count(current)) {
            for (const auto& [next, cost] : fibres_[current]) {
                Cost newDist = currentDist + cost;
                
                // If found a better path to next
                if (!distance.count(next) || newDist < distance[next]) {
                    distance[next] = newDist;
                    parent[next] = current;
                    pq.push({newDist, next});
                }
            }
        }
    }
    
    // If no path found
    if (!found) {
        return result;
    }
    
    // Reconstruct path
    std::vector<std::pair<Coord, Cost>> path;
    Coord node = toxpoint;
    
    while (node != NO_COORD) {
        path.push_back({node, distance[node]});
        node = parent[node];
    }
    
    std::reverse(path.begin(), path.end());
    return path;
}

// Returns a cycle of fibres starting and ending at the given crossing point
std::vector<Coord> Datastructures::route_fibre_cycle(Coord startxpoint)
{
     std::vector<Coord> result;
    
    // Check if starting point exists
    if (!fibres_.count(startxpoint)) {
        return result;
    }
    
    // DFS to detect cycle
    std::unordered_map<Coord, bool, CoordHash> visited;
    std::unordered_map<Coord, Coord, CoordHash> parent;
    std::vector<Coord> path;
    
    std::function<bool(Coord, Coord)> dfs = [&](Coord current, Coord prev) -> bool {
        visited[current] = true;
        path.push_back(current);
        
        if (fibres_.count(current)) {
            for (const auto& [next, cost] : fibres_[current]) {
                // Skip the edge i came from (undirected graph)
                if (next == prev) {
                    continue;
                }
                
                // If found a visited node, found a cycle
                if (visited[next]) {
                    // Add the node where cycle closes
                    path.push_back(next);
                    return true;
                }
                
                // Recursively explore
                parent[next] = current;
                if (dfs(next, current)) {
                    return true;
                }
            }
        }
        
        path.pop_back();
        return false;
    };
    
    // Start DFS from the given point
    if (dfs(startxpoint, NO_COORD)) {
        return path;
    }
    
    return result;
}



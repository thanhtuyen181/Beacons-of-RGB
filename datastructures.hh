// Datastructures.hh

#ifndef DATASTRUCTURES_HH
#define DATASTRUCTURES_HH

#include <string>
#include <vector>
#include <utility>
#include <limits>
#include <unordered_map>
#include <algorithm>
#include <functional>
#include <exception>
#include <cstddef>
#include <map>

#include <source_location>


// Type for beacon IDs
using BeaconID = std::string;
using Name = std::string;

// Return value for cases where required beacon was not found
BeaconID const NO_BEACON= "--NO_BEACON--";

// Return value for cases where integer values were not found
int const NO_VALUE = std::numeric_limits<int>::min();

// Return value for cases where name values were not found
Name const NO_NAME = "-- NO_NAME --";

// Type for a coordinate (x, y)
struct Coord
{
    int x = NO_VALUE;
    int y = NO_VALUE;
};

// Example: Defining == and hash function for Coord so that it can be used
// as key for std::unordered_map/set, if needed
inline bool operator==(Coord c1, Coord c2) { return c1.x == c2.x && c1.y == c2.y; }
inline bool operator!=(Coord c1, Coord c2) { return !(c1==c2); } // Not strictly necessary

struct CoordHash
{
    std::size_t operator()(Coord xy) const
    {
        auto hasher = std::hash<int>();
        auto xhash = hasher(xy.x);
        auto yhash = hasher(xy.y);
        // Combine hash values (magic!)
        return xhash ^ (yhash + 0x9e3779b9 + (xhash << 6) + (xhash >> 2));
    }
};

// Example: Defining < for Coord so that it can be used
// as key for std::map/set
inline bool operator<(Coord c1, Coord c2)
{
    if (c1.y < c2.y) { return true; }
    else if (c2.y < c1.y) { return false; }
    else { return c1.x < c2.x; }
}

// Return value for cases where coordinates were not found
Coord const NO_COORD = {NO_VALUE, NO_VALUE};

// Type for color (RGB)
struct Color
{
    int r = NO_VALUE;
    int g = NO_VALUE;
    int b = NO_VALUE;
};

// Equality and non-equality comparisons for Colors
inline bool operator==(Color c1, Color c2) { return c1.r == c2.r && c1.g == c2.g && c1.b == c2.b; }
inline bool operator!=(Color c1, Color c2) { return !(c1==c2); }

// Return value for cases where color was not found
Color const NO_COLOR = {NO_VALUE, NO_VALUE, NO_VALUE};

// Type for light transmission cost (used only in the second assignment)
using Cost = int;

// Return value for cases where cost is unknown
Cost const NO_COST = NO_VALUE;

// This exception class is there just so that the user interface can notify
// about operations which are not (yet) implemented
class NotImplemented : public std::exception
{
public:
    explicit NotImplemented(std::string const msg = "",
                            const std::source_location location = std::source_location::current())
        : msg_{}
    {
        std::string funcname = location.function_name();
        if (auto namestart = funcname.find_last_of(':'); namestart != std::string::npos)
        { funcname.erase(0, namestart+1); }
        if (auto nameend = funcname.find_first_of('('); nameend != std::string::npos)
        { funcname.erase(nameend, std::string::npos); }
        msg_ = (!msg.empty() ? msg+" in " : "")+funcname+"()";
    }

    virtual const char* what() const noexcept override
    {
        return msg_.c_str();
    }
private:
    std::string msg_;
};

// This is the class you are supposed to implement

class Datastructures
{
public:
    Datastructures();
    ~Datastructures();

    // A operations

    // Estimate of performance: O(1)
    // Short rationale for estimate: Inserting into an unordered_map is average O(1)
    bool add_beacon(BeaconID id, Name const& name, Coord xy, Color color);

    // Estimate of performance: O(1)
    // Short rationale for estimate: Checking existence in an unordered_map is average O(1)
    int beacon_count();

    // Estimate of performance: O(1)
    // Short rationale for estimate: Clearing an unordered_map is O(1)
    void clear_beacons();

    // Estimate of performance: O(n)
    // Short rationale for estimate: Iterating through all beacons in an unordered_map is O(n)
    std::vector<BeaconID> all_beacons();

    // Estimate of performance: O(1)
    // Short rationale for estimate: Accessing an element in an unordered_map is average O(1)
    Name get_name(BeaconID id);

    // Estimate of performance: O(1)
    // Short rationale for estimate: Accessing an element in an unordered_map is average O(1)
    Coord get_coordinates(BeaconID id);

    // Estimate of performance: O(1)
    // Short rationale for estimate: Accessing an element in an unordered_map is average O(1)
    Color get_color(BeaconID id);

    // We recommend you implement the operations below only after implementing the ones above

    // Estimate of performance: O(n log n)
    // Short rationale for estimate: Sorting n elements is O(n log n)
    std::vector<BeaconID> beacons_alphabetically();

    // Estimate of performance: O(n log n)
    // Short rationale for estimate: Sorting n elements is O(n log n)
    std::vector<BeaconID> beacons_brightness_increasing();

    // Estimate of performance: O(n)
    // Short rationale for estimate: Finding min element in n elements is O(n)
    BeaconID min_brightness();

    // Estimate of performance: O(n)
    // Short rationale for estimate: Finding max element in n elements is O(n)
    BeaconID max_brightness();

    // Estimate of performance: O(n)
    // Short rationale for estimate: Finding elements in n elements is O(n)
    std::vector<BeaconID> find_beacons(Name const& name);

    // Estimate of performance: O(1)
    // Short rationale for estimate: Accessing and modifying an element in an unordered_map is average O(1)
    bool change_beacon_name(BeaconID id, Name const& newname);

    // We recommend you implement the operations below only after implementing the ones above

    // Estimate of performance: O(1)
    // Short rationale for estimate: Accessing and modifying an element in an unordered_map is average O(1)
    bool add_lightbeam(BeaconID sourceid, BeaconID targetid);

    // Estimate of performance: O(k log k)
    // Short rationale for estimate: Retrieving k incoming beams is O(k), sorting them is O(k log k)
    std::vector<BeaconID> get_lightsources(BeaconID id);

    // Estimate of performance: O(k)
    // Short rationale for estimate: Traversing k elements in a path is O(k)
    std::vector<BeaconID> path_outbeam(BeaconID id);

    // B operations

    // Estimate of performance: O(k)
    // Short rationale for estimate: Traversing k elements in the longest path is O(k)
    std::vector<BeaconID> path_inbeam_longest(BeaconID id);

    // Estimate of performance: O(n)
    // Short rationale for estimate: Accessing an element in an unordered_map is average O(1)
    Color total_color(BeaconID id);

    // Estimate of performance: O(log n)
    // Short rationale for estimate: Inserting into a map is O(log n)
    bool add_fibre(Coord xpoint1, Coord xpoint2, Cost cost);

    // Estimate of performance: O(n)
    // Short rationale for estimate: Iterating through all keys in a map is O(n)
    std::vector<Coord> all_xpoints();

    // Estimate of performance: O(k)
    // Short rationale for estimate: Retrieving k fibres from a point is O(k)
    std::vector<std::pair<Coord, Cost>> get_fibres_from(Coord xpoint);

    // Estimate of performance: O(m)
    // Short rationale for estimate: Iterating through all fibres is O(m)
    std::vector<std::pair<Coord, Coord>> all_fibres();

    // Estimate of performance: O(k)
    // Short rationale for estimate: Removing a fibre involves checking existence and erasing from two maps, each O(log k)
    bool remove_fibre(Coord xpoint1, Coord xpoint2);

    // Estimate of performance: O(n)
    // Short rationale for estimate: Clearing all fibres involves clearing the map, which is O(n)
    void clear_fibres();

    // We recommend you implement the operations below only after implementing the ones above

    // Estimate of performance: O(k)
    // Short rationale for estimate: BFS traversal through k nodes in the path is O(k)
    std::vector<std::pair<Coord, Cost>> route_any(Coord fromxpoint, Coord toxpoint);

    // C operations

    // Estimate of performance: O(V + E)
    // Short rationale for estimate: BFS traverses vertices and edges once to find path with fewest xpoints
    std::vector<std::pair<Coord, Cost>> route_least_xpoints(Coord fromxpoint, Coord toxpoint);

    // Estimate of performance: O(k log k)
    // Short rationale for estimate: Dijkstra's algorithm involves a priority queue with log k operations for k nodes
    std::vector<std::pair<Coord, Cost>> route_fastest(Coord fromxpoint, Coord toxpoint);

    // Estimate of performance: O(V + E)
    // Short rationale for estimate: DFS traverses vertices and edges once to detect cycle
    std::vector<Coord> route_fibre_cycle(Coord startxpoint);

private:
    // Explain below your rationale for choosing the data structures you use in this class.
    // Beacons are stored in an unordered_map for O(1) average access by ID.
    // Each beacon tracks its outgoing light beam and incoming light beams.
    // Fibres (edges) are stored in an unordered_map indexed by the first coordinate,
    // with each value being a map from second coordinate to cost.
    // This allows O(1) average lookup of fibres from a given point.

    // Add stuff needed for your class implementation below
    struct Beacon {
        Name name;
        Coord xy;
        Color color;

        BeaconID outgoing = NO_BEACON;          // The beacon this one points to
        std::vector<BeaconID> incoming;         // Beacons that point to this one
    };

    // Structure to store fibres: map from first coord to (second coord, cost) pairs
    // We need to efficiently find fibres from a point and check if a fibre exists
    struct FibreEdge {
        Coord target;
        Cost cost;
    };

    std::unordered_map<BeaconID, Beacon> beacons_;
    
    // Store fibres using a nested map structure for efficient lookups
    // coord -> (target_coord -> cost)
    std::map<Coord, std::map<Coord, Cost>> fibres_;

};

#endif // DATASTRUCTURES_HH

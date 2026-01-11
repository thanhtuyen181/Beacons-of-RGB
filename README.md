# Beacons of RGB 🌈

**Data Structures & Algorithms Course Project (C++20)**

## Overview

**Beacons of RGB** is a C++ project developed for a **Data Structures and Algorithms** course at Tampere University.  
The project simulates a network of beacons that emit, combine, and transmit RGB light through directed light beams and underground optical fibers.

- **Grade:** ⭐ 48 / 50  
- **Language:** C++20  
- **Focus:** Algorithmic efficiency, STL usage, graph traversal, clean design

## Project goals

- Practice effective use of C++ STL containers and algorithms
- Implement efficient searching, sorting, and graph algorithms
- Analyze and optimize time complexity of frequently called operations
- Maintain a clean separation between provided framework code and student implementation

## Real-World Relevance & Impact

This project goes beyond a purely academic exercise by modeling problems that appear frequently in real-world systems. At its core, it simulates a network of nodes (beacons) and computes efficient routes between them, which directly reflects how modern infrastructure operates.

Similar concepts are used in:

- **GPS navigation systems**, where shortest or most efficient paths must be calculated dynamically

- **Computer networks**, where data packets are routed through multiple nodes

- **Logistics and delivery systems**, which optimize routes to reduce time and cost

- **Smart cities and IoT networks**, where sensors and devices communicate through distributed nodes

By visualizing the routing process instead of only printing numerical results, the project makes abstract algorithms tangible and easier to understand. This mirrors real engineering practice, where systems must be both correct and observable for debugging and optimization.

## Core concepts implemented

- Hash-based and ordered data structures (`unordered_map`, `map`, `set`, `vector`)
- Directed graphs (light beam connections)
- Undirected weighted graphs (optical fiber network)
- Graph traversal algorithms (BFS, DFS, Dijkstra-style routing)
- Custom sorting and aggregation logic
- Performance-aware design (avoiding unnecessary recomputation)

## Features

### Beacon management

- Add, remove, and query beacons by ID
- Store beacon metadata: name, coordinates, RGB color
- Sort beacons:
  - Alphabetically
  - By brightness
- Query:
  - Brightest / dimmest beacon
  - Beacons with the same name

### Light beam system

- Directed light transmission between beacons
- Incoming light rays are combined by averaging RGB values
- Brightness computed using:
```
brightness = 3*r + 6*g + b
```
- Supported operations:
  - Incoming light sources
  - Outgoing light paths
  - Longest incoming light chain
  - Final combined color output

### Optical fiber network

- Add and remove underground optical fibers
- Fibers are bidirectional and weighted (cost = time)
- Query all intersection points and outgoing fibers

### Routing algorithms

- Find any valid route between two points
- Find route with:
  - Fewest intersections
  - Lowest total cost (fastest route)
- Detect cycles in the fiber network

## Performance considerations

Efficiency was a key grading criterion:

- Frequently called operations optimized to O(1) or O(log n) where possible
- Sorting only when required
- Selective precomputation and caching
- Implementations respect the guideline: average-case complexity should not exceed Θ(n log n)

## Testing & visualization

Integrated with a pre-built main program supporting:

- Text-based command execution (g++)
- QtCreator graphical UI
- Automated correctness testing
- Performance benchmarking
- Visual rendering of beacons, beams, and fiber routes

No modifications were made to the provided framework files.

## Project structure

```
.
├── datastructures.hh     # Public interface (provided incomplete, student code to complete)
├── datastructures.cc     # Core implementation (student work)
├── course_code/          # Provided framework & UI files
└── README.md
```

## How to run

Compile and run using either:

- Command-line (g++) for text-based interaction
- QtCreator / qmake for graphical visualization

Behavior and functionality are identical in both modes.

## GUI preview on QT Creator

<img width="908" height="688" alt="A screenshot of the user interface after adding beacons, lightbeams, and fibres" src="https://github.com/user-attachments/assets/2a2a7db4-0942-44d5-b551-7f4b44879771" />

_A screenshot of the user interface after adding beacons, lightbeams, and fibres._

<img width="714" height="906" alt="A screenshot of the list of commands available" src="https://github.com/user-attachments/assets/1495a5ee-0b18-4574-94cb-342c1295b52e" />

_A screenshot of the list of commands available._

## Final notes

This project focuses on algorithmic thinking, clean data modeling, scalability, and practical use of STL. It is a solid example of practical C++ applied to non-trivial algorithmic problems.

## Author

**Truong Thanh Tuyen**  
Computing and Electrical Engineering Student — Tampere University





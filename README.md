# Beacons of RGB 🌈

**Data Structures & Algorithms Course Project (C++20)**

## Overview

**Beacons of RGB** is a C++ project developed for a **Data Structures and Algorithms** course at Tampere University.  
The project simulates a network of mystical beacons that emit, combine, and transmit RGB light through directed light beams and underground optical fibers.

- **Grade:** ⭐ 48 / 50  
- **Language:** C++20  
- **Focus:** Algorithmic efficiency, STL usage, graph traversal, clean design

## Project goals

- Practice effective use of C++ STL containers and algorithms
- Implement efficient searching, sorting, and graph algorithms
- Analyze and optimize time complexity of frequently called operations
- Maintain a clean separation between provided framework code and student implementation

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

## Final notes

This project focuses on algorithmic thinking, clean data modeling, scalability, and practical use of STL. It is a solid example of practical C++ applied to non-trivial algorithmic problems.

## Author

**Truong Thanh Tuyen**  
Computing and Electrical Engineering Student — Tampere University


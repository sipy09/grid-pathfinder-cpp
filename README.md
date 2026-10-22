# Grid Pathfinder — C++17

A small, dependency-free **game-map pathfinding** project written in modern C++.
It uses **breadth-first search (BFS)** to find a shortest route through an ASCII
map, avoiding walls. All steps cost the same, so BFS guarantees a shortest route
when one exists.

## Demo

```text
Original map:
S#G
...

Shortest path (4 moves):
S#G
***
```

The demo runs in a **terminal**, not a graphical window. The default map has a
shortest route of 19 moves.

## Features

- Grid representation and input validation (rectangular map, one `S`, one `G`)
- Shortest-path BFS using `std::queue` and parent-index reconstruction
- Clear `S` / `G` markers and `*` path overlay
- Built-in level plus loadable custom map files
- Standalone C++17, no external libraries or graphics framework required
- Automated tests covering valid, blocked, minimal, and malformed maps

## Build and run (macOS, Linux)

Requirements: a C++17 compiler and CMake 3.16 or newer. No raylib needed.

```bash
cmake -S . -B build
cmake --build build
ctest --test-dir build --output-on-failure
./build/grid_pathfinder
```

Load a custom map or view the CLI help:

```bash
./build/grid_pathfinder maps/simple.txt
./build/grid_pathfinder maps/blocked.txt
./build/grid_pathfinder maps/maze.txt
./build/grid_pathfinder --help
```

Direct compilation without CMake:

```bash
clang++ -std=c++17 -Wall -Wextra -Wpedantic src/pathfinder.cpp src/main.cpp -o grid_pathfinder
./grid_pathfinder
```

## Map format

Plain UTF-8/ASCII text with equal-length rows and **exactly one** start and goal:

| Symbol | Meaning |
|---|---|
| `S` | Start position |
| `G` | Goal position |
| `.` | Walkable tile |
| `#` | Wall (impassable) |
| `*` | Rendered shortest-path tile (output only) |

Movement is orthogonal (up/down/left/right), not diagonal. If the goal cannot
be reached, the program prints `No route to the goal.` Invalid input produces
an error message and a nonzero exit code.

## Architecture

```text
grid-pathfinder-cpp/
├── CMakeLists.txt          Build configuration + CTest
├── src/
│   ├── main.cpp            CLI, map loading, and output
│   ├── pathfinder.hpp      Grid and Point interfaces
│   └── pathfinder.cpp      Validation, rendering, BFS
├── tests/
│   └── test_pathfinder.cpp Assertion-based automated tests
├── maps/
│   ├── simple.txt          Four-move detour
│   ├── blocked.txt         No route available
│   └── maze.txt            Larger sample level
├── .github/workflows/ci.yml  Build + tests on GitHub Actions
├── GHID_RO.md             Romanian setup and interview notes
├── LICENSE                MIT license
├── .gitignore
└── README.md
```

## Algorithm and complexity

BFS expands positions in increasing distance from the start. Each tile is visited
at most once. With `R` rows and `C` columns, the time and space complexity are
**O(R × C)**. The path includes both `S` and `G`, so the number of moves equals
`path.size() - 1`.

## Future extensions

- Add A* (Manhattan heuristic) and measure explored-cell counts against BFS.
- Add weighted terrain and Dijkstra's algorithm.
- Add an interactive 2D view or integrate the algorithm into a larger game.

## Project scope

This is a small terminal algorithm demo, **not** a mobile game or a Unity/C#
project. Review the code and make changes you can explain before using it in an
interview. The initial project package was assembled with AI assistance.

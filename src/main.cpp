#include "pathfinder.hpp"

#include <exception>
#include <fstream>
#include <iostream>
#include <stdexcept>
#include <string>
#include <vector>

namespace {
std::vector<std::string> load_map(const std::string& filename) {
    std::ifstream file(filename);
    if (!file) {
        throw std::runtime_error("Cannot open map file: " + filename);
    }
    std::vector<std::string> rows;
    std::string line;
    while (std::getline(file, line)) {
        if (!line.empty() && line.back() == '\r') {
            line.pop_back(); // Accept Windows-style CRLF files.
        }
        rows.push_back(line);
    }
    if (file.bad()) {
        throw std::runtime_error("Failed while reading map: " + filename);
    }
    return rows;
}
} // namespace

int main(int argc, char* argv[]) {
    if (argc == 2 && std::string(argv[1]) == "--help") {
        std::cout << "Usage: grid_pathfinder [map-file]\n"
                     "Without a file, runs the built-in demo.\n"
                     "Map tiles: S=start, G=goal, .=floor, #=wall.\n";
        return 0;
    }
    if (argc > 2) {
        std::cerr << "Usage: grid_pathfinder [map-file]\n";
        return 1;
    }

    try {
        const std::vector<std::string> cells = argc == 2
            ? load_map(argv[1])
            : std::vector<std::string>{
                "S...#.......",
                ".##.#.#####.",
                "...#........",
                ".#.###.###..",
                "...#...#....",
                "##...#...##.",
                ".....#.....G",
            };
        const Grid grid(cells);
        const auto path = shortest_path(grid);
        std::cout << "Original map:\n" << grid.render();
        if (path.empty()) {
            std::cout << "No route to the goal.\n";
            return 0;
        }
        std::cout << "Shortest path (" << path.size() - 1 << " moves):\n"
                  << grid.render(path);
        return 0;
    } catch (const std::exception& error) {
        std::cerr << "Error: " << error.what() << '\n';
        return 1;
    }
}

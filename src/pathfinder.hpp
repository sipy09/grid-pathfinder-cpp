#pragma once

#include <string>
#include <vector>

struct Point {
    int row = 0;
    int col = 0;
    bool operator==(const Point& other) const {
        return row == other.row && col == other.col;
    }
};

class Grid {
public:
    explicit Grid(std::vector<std::string> cells);
    int rows() const;
    int cols() const;
    bool walkable(Point p) const;
    Point start() const;
    Point goal() const;
    std::string render(const std::vector<Point>& path = {}) const;

private:
    std::vector<std::string> cells_;
    Point start_;
    Point goal_;
};

// Breadth-first search finds the shortest path for an unweighted grid.
// Includes both S and G in the returned path; empty means unreachable.
std::vector<Point> shortest_path(const Grid& grid);

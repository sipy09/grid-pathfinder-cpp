#include "pathfinder.hpp"

#include <algorithm>
#include <queue>
#include <sstream>
#include <stdexcept>

Grid::Grid(std::vector<std::string> cells) : cells_(std::move(cells)) {
    if (cells_.empty() || cells_[0].empty()) {
        throw std::invalid_argument("Grid cannot be empty");
    }
    const auto width = cells_[0].size();
    int starts = 0, goals = 0;
    for (int r = 0; r < static_cast<int>(cells_.size()); ++r) {
        if (cells_[r].size() != width) {
            throw std::invalid_argument("Every grid row must have equal width");
        }
        for (int c = 0; c < static_cast<int>(width); ++c) {
            switch (cells_[r][c]) {
                case 'S': start_ = {r, c}; ++starts; break;
                case 'G': goal_ = {r, c}; ++goals; break;
                case '.': case '#': break;
                default: throw std::invalid_argument("Unexpected map character");
            }
        }
    }
    if (starts != 1 || goals != 1) {
        throw std::invalid_argument("Grid must contain exactly one S and one G");
    }
}

int Grid::rows() const { return static_cast<int>(cells_.size()); }
int Grid::cols() const { return static_cast<int>(cells_[0].size()); }
bool Grid::walkable(Point p) const {
    return p.row >= 0 && p.row < rows() && p.col >= 0 && p.col < cols()
           && cells_[p.row][p.col] != '#';
}
Point Grid::start() const { return start_; }
Point Grid::goal() const { return goal_; }

std::string Grid::render(const std::vector<Point>& path) const {
    auto output = cells_;
    for (const Point p : path) {
        if (!(p == start_) && !(p == goal_) && walkable(p)) {
            output[p.row][p.col] = '*';
        }
    }
    std::ostringstream lines;
    for (const auto& line : output) lines << line << '\n';
    return lines.str();
}

std::vector<Point> shortest_path(const Grid& grid) {
    const int width = grid.cols();
    const int total = grid.rows() * width;
    const auto index = [width](Point p) { return p.row * width + p.col; };
    const Point start = grid.start();
    const Point goal = grid.goal();

    std::vector<int> parent(total, -1);
    std::queue<Point> frontier;
    frontier.push(start);
    parent[index(start)] = index(start);

    constexpr int dr[] = {-1, 1, 0, 0};
    constexpr int dc[] = {0, 0, -1, 1};
    while (!frontier.empty()) {
        Point current = frontier.front();
        frontier.pop();
        if (current == goal) break;
        for (int direction = 0; direction < 4; ++direction) {
            Point next{current.row + dr[direction], current.col + dc[direction]};
            if (grid.walkable(next) && parent[index(next)] == -1) {
                parent[index(next)] = index(current);
                frontier.push(next);
            }
        }
    }
    if (parent[index(goal)] == -1) return {};

    std::vector<Point> path;
    int cursor = index(goal);
    while (cursor != index(start)) {
        path.push_back({cursor / width, cursor % width});
        cursor = parent[cursor];
    }
    path.push_back(start);
    std::reverse(path.begin(), path.end());
    return path;
}

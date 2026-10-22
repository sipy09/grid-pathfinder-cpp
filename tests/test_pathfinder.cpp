#include "pathfinder.hpp"

#include <cstdlib>
#include <iostream>
#include <stdexcept>
#include <string>
#include <vector>

namespace {
int failures = 0;

void expect(bool condition, const std::string& description) {
    if (!condition) {
        ++failures;
        std::cerr << "FAIL: " << description << '\n';
    } else {
        std::cout << "PASS: " << description << '\n';
    }
}

template <typename Function>
void expect_invalid(Function action, const std::string& description) {
    try {
        action();
        expect(false, description);
    } catch (const std::invalid_argument&) {
        expect(true, description);
    } catch (...) {
        expect(false, description + " (unexpected exception type)");
    }
}

void test_adjacent() {
    const Grid grid({"SG"});
    const auto path = shortest_path(grid);
    expect(path.size() == 2, "adjacent S/G: one move");
    expect(path == std::vector<Point>({{0, 0}, {0, 1}}), "adjacent S/G: expected path");
    expect(grid.render(path) == "SG\n", "render preserves S and G");
}

void test_obstacle_and_shortest_path() {
    const Grid grid({"S#G", "..."});
    const auto path = shortest_path(grid);
    expect(path.size() == 5, "detour: shortest path has four moves");
    expect(path.front() == grid.start() && path.back() == grid.goal(), "detour: endpoints correct");
    for (std::size_t i = 1; i < path.size(); ++i) {
        const int dr = path[i].row - path[i - 1].row;
        const int dc = path[i].col - path[i - 1].col;
        expect(dr * dr + dc * dc == 1, "detour: every move is orthogonally adjacent");
        expect(grid.walkable(path[i]), "detour: every tile is walkable");
    }
    expect(grid.render(path) == "S#G\n***\n", "detour: renders route correctly");
}

void test_unreachable() {
    const Grid grid({"S#G"});
    expect(shortest_path(grid).empty(), "unreachable goal returns empty path");
}

void test_boundaries() {
    const Grid grid({"S#", ".G"});
    expect(!grid.walkable({-1, 0}), "negative row blocked");
    expect(!grid.walkable({0, -1}), "negative column blocked");
    expect(!grid.walkable({2, 0}), "row outside grid blocked");
    expect(!grid.walkable({0, 2}), "column outside grid blocked");
    expect(!grid.walkable({0, 1}), "wall blocked");
    expect(grid.walkable({1, 1}), "goal walkable");
}

void test_input_validation() {
    expect_invalid([] { Grid grid({}); }, "reject empty grid");
    expect_invalid([] { Grid grid({""}); }, "reject empty rows");
    expect_invalid([] { Grid grid({"S.G", ".."}); }, "reject unequal row widths");
    expect_invalid([] { Grid grid({"..."}); }, "reject missing start and goal");
    expect_invalid([] { Grid grid({"S.."}); }, "reject missing goal");
    expect_invalid([] { Grid grid({"SGS"}); }, "reject duplicate start");
    expect_invalid([] { Grid grid({"SGG"}); }, "reject duplicate goal");
    expect_invalid([] { Grid grid({"SXG"}); }, "reject unknown symbols");
}
} // namespace

int main() {
    test_adjacent();
    test_obstacle_and_shortest_path();
    test_unreachable();
    test_boundaries();
    test_input_validation();
    if (failures != 0) {
        std::cerr << failures << " test assertion(s) failed.\n";
        return EXIT_FAILURE;
    }
    std::cout << "All pathfinder assertions passed.\n";
    return EXIT_SUCCESS;
}

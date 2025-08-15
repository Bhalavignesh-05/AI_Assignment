// 01_british_museum_search.cpp
#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <stack>
#include <algorithm>
#include <limits>

using Graph = std::map<char, std::vector<std::pair<char, int>>>;
using PathResult = std::pair<std::vector<char>, int>;

const Graph graph = {
    {'A', {{'B', 4}, {'C', 3}}},
    {'B', {{'A', 4}, {'D', 5}, {'E', 12}}},
    {'C', {{'A', 3}, {'D', 7}, {'F', 10}}},
    {'D', {{'B', 5}, {'C', 7}, {'E', 2}}},
    {'E', {{'B', 12}, {'D', 2}, {'G', 5}}},
    {'F', {{'C', 10}, {'G', 3}}},
    {'G', {{'E', 5}, {'F', 3}}}
};
const char START_NODE = 'A';
const char GOAL_NODE = 'G';

int calculate_cost(const Graph& g, const std::vector<char>& path) {
    if (path.size() < 2) return 0;
    int cost = 0;
    for (size_t i = 0; i < path.size() - 1; ++i) {
        char u = path[i];
        char v = path[i+1];
        for (const auto& edge : g.at(u)) {
            if (edge.first == v) {
                cost += edge.second;
                break;
            }
        }
    }
    return cost;
}

void print_result(const std::string& algo_name, const PathResult& result) {
    std::cout << "--- " << algo_name << " ---" << std::endl;
    if (result.second == -1) {
        std::cout << "Path not found." << std::endl;
    } else {
        std::cout << "Path: ";
        for (size_t i = 0; i < result.first.size(); ++i) {
            std::cout << result.first[i] << (i == result.first.size() - 1 ? "" : " -> ");
        }
        std::cout << "\nCost: " << result.second << std::endl;
    }
}

PathResult british_museum_search(const Graph& g, char start, char goal) {
    std::stack<std::vector<char>> s;
    s.push({start});

    PathResult best_result = {{}, -1};

    while (!s.empty()) {
        std::vector<char> current_path = s.top();
        s.pop();
        char last_node = current_path.back();

        if (last_node == goal) {
            int current_cost = calculate_cost(g, current_path);
            if (best_result.second == -1 || current_cost < best_result.second) {
                best_result = {current_path, current_cost};
            }
            continue;
        }

        for (const auto& edge : g.at(last_node)) {
            char neighbor = edge.first;
            if (std::find(current_path.begin(), current_path.end(), neighbor) == current_path.end()) {
                std::vector<char> new_path = current_path;
                new_path.push_back(neighbor);
                s.push(new_path);
            }
        }
    }
    return best_result;
}

int main() {
    PathResult result = british_museum_search(graph, START_NODE, GOAL_NODE);
    print_result("British Museum Search", result);
    return 0;
}
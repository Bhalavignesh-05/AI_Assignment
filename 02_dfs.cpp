// 02_dfs.cpp
#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <stack>
#include <algorithm>

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
        bool found = false;
        for (const auto& edge : g.at(u)) {
            if (edge.first == v) {
                cost += edge.second;
                found = true;
                break;
            }
        }
        if (!found) return -1; 
    }
    return cost;
}

// Prints the result in a standard format.
void print_result(const std::string& algo_name, const PathResult& result) {
    std::cout << "--- " << algo_name << " ---" << std::endl;
    if (result.second == -1 || result.first.empty()) {
        std::cout << "Path not found." << std::endl;
    } else {
        std::cout << "Path: ";
        for (size_t i = 0; i < result.first.size(); ++i) {
            std::cout << result.first[i] << (i == result.first.size() - 1 ? "" : " -> ");
        }
        std::cout << "\nCost: " << result.second << std::endl;
    }
}

PathResult dfs(const Graph& g, char start, char goal) {
    std::stack<std::vector<char>> s;
    s.push({start});

    while (!s.empty()) {
        std::vector<char> current_path = s.top();
        s.pop();
        char last_node = current_path.back();

        if (last_node == goal) {
            return {current_path, calculate_cost(g, current_path)};
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
    return {{}, -1};
}

int main() {
    PathResult result = dfs(graph, START_NODE, GOAL_NODE);
    print_result("Depth-First Search (DFS)", result);
    return 0;
}
// 05_dfs_history.cpp
#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <stack>
#include <set>

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

PathResult dfs_history(const Graph& g, char start, char goal) {
    std::stack<std::vector<char>> s;
    s.push({start});
    std::set<char> visited_global;

    while (!s.empty()) {
        std::vector<char> path = s.top();
        s.pop();
        char current_node = path.back();

        if (visited_global.count(current_node)) continue;
        visited_global.insert(current_node);

        if (current_node == goal) {
            return {path, calculate_cost(g, path)};
        }
        
        for (const auto& edge : g.at(current_node)) {
            if (visited_global.find(edge.first) == visited_global.end()) {
                std::vector<char> new_path = path;
                new_path.push_back(edge.first);
                s.push(new_path);
            }
        }
    }
    return {{}, -1};
}

int main() {
    PathResult result = dfs_history(graph, START_NODE, GOAL_NODE);
    print_result("DFS with History", result);
    return 0;
}
// 03_bfs_ucs.cpp
#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <queue>
#include <functional>

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

PathResult bfs_ucs(const Graph& g, char start, char goal) {
    using State = std::pair<int, std::vector<char>>;
    std::priority_queue<State, std::vector<State>, std::greater<State>> pq;

    pq.push({0, {start}});
    std::map<char, int> cost_so_far;
    cost_so_far[start] = 0;

    while (!pq.empty()) {
        int current_cost = pq.top().first;
        std::vector<char> current_path = pq.top().second;
        pq.pop();
        char last_node = current_path.back();

        if (last_node == goal) {
            return {current_path, current_cost};
        }
        if (current_cost > cost_so_far[last_node]) {
            continue;
        }

        for (const auto& edge : g.at(last_node)) {
            char neighbor = edge.first;
            int new_cost = current_cost + edge.second;
            if (cost_so_far.find(neighbor) == cost_so_far.end() || new_cost < cost_so_far[neighbor]) {
                cost_so_far[neighbor] = new_cost;
                std::vector<char> new_path = current_path;
                new_path.push_back(neighbor);
                pq.push({new_cost, new_path});
            }
        }
    }
    return {{}, -1};
}

int main() {
    PathResult result = bfs_ucs(graph, START_NODE, GOAL_NODE);
    print_result("BFS (Uniform Cost Search)", result);
    return 0;
}
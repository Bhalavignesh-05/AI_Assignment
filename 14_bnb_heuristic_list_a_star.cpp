// 14_bnb_heuristic_list_a_star.cpp
#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <queue>
#include <functional>
#include <tuple>

using Graph = std::map<char, std::vector<std::pair<char, int>>>;
using Heuristics = std::map<char, int>;
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

const Heuristics heuristics = {
    {'A', 10}, {'B', 11}, {'C', 12}, {'D', 6}, {'E', 4}, {'F', 2}, {'G', 0}
};

const char START_NODE = 'A';
const char GOAL_NODE = 'G';

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

PathResult a_star(const Graph& g, const Heuristics& h, char start, char goal) {
    using State = std::tuple<int, int, std::vector<char>>;
    std::priority_queue<State, std::vector<State>, std::greater<State>> pq;
    std::map<char, int> cost_so_far;

    pq.push({h.at(start), 0, {start}});
    cost_so_far[start] = 0;

    while(!pq.empty()){
        State top_element = pq.top();
        int g_cost = std::get<1>(top_element);
        std::vector<char> path = std::get<2>(top_element);

        pq.pop();

        char last_node = path.back();

        if (g_cost > cost_so_far[last_node]) continue;
        if (last_node == goal) return {path, g_cost};

        for(const auto& edge : g.at(last_node)){
            char neighbor = edge.first;
            int new_g_cost = g_cost + edge.second;

            if (cost_so_far.find(neighbor) == cost_so_far.end() || new_g_cost < cost_so_far[neighbor]) {
                cost_so_far[neighbor] = new_g_cost;
                int priority = new_g_cost + h.at(neighbor);
                std::vector<char> new_path = path;
                new_path.push_back(neighbor);
                pq.push({priority, new_g_cost, new_path});
            }
        }
    }
    return {{}, -1};
}

int main() {
    PathResult result = a_star(graph, heuristics, START_NODE, GOAL_NODE);
    print_result("B&B with Heuristics + List (A*)", result);
    return 0;
}
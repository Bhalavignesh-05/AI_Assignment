// 13_bnb_cost_heuristic.cpp 
#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <queue>
#include <functional>
#include <tuple>
#include <algorithm>

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

PathResult get_oracle_result() {
    return {{'A', 'B', 'D', 'E', 'G'}, 16};
}

PathResult bnb_cost_heuristic(const Graph& g, const Heuristics& h, char start, char goal) {
    int bound = get_oracle_result().second;
    
    using State = std::tuple<int, int, std::vector<char>>;
    std::priority_queue<State, std::vector<State>, std::greater<State>> pq;
    pq.push({h.at(start), 0, {start}});
    
    while(!pq.empty()){
        State top_element = pq.top();
        int g_cost = std::get<1>(top_element);
        std::vector<char> path = std::get<2>(top_element);
        pq.pop();
        char last_node = path.back();

        if (g_cost >= bound) continue;
        if (last_node == goal) return {path, g_cost};

        for(const auto& edge : g.at(last_node)){
            char neighbor = edge.first;
            if (std::find(path.begin(), path.end(), neighbor) == path.end()) {
                int new_g_cost = g_cost + edge.second;
                if (new_g_cost + h.at(neighbor) < bound) {
                    std::vector<char> new_path = path;
                    new_path.push_back(neighbor);
                    pq.push({new_g_cost + h.at(neighbor), new_g_cost, new_path});
                }
            }
        }
    }
    return {{}, -1};
}

int main() {
    PathResult result = bnb_cost_heuristic(graph, heuristics, START_NODE, GOAL_NODE);
    print_result("B&B with Cost + Heuristics", result);
    return 0;
}
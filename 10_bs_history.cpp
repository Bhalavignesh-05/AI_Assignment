// 10_bs_history.cpp 
#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <set>          
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

PathResult beam_search_history(const Graph& g, const Heuristics& h, char start, char goal, int beam_width) {
    std::vector<std::vector<char>> beam;
    beam.push_back({start});

    std::set<char> visited;
    visited.insert(start);
    
    while(true){
        std::vector<std::pair<int, std::vector<char>>> candidates;
        for(const auto& path : beam){
            char last_node = path.back();
            if(last_node == goal) return {path, calculate_cost(g, path)};
            
            for(const auto& edge : g.at(last_node)){
                 if (visited.find(edge.first) == visited.end()){
                    std::vector<char> new_path = path;
                    new_path.push_back(edge.first);
                    candidates.push_back({h.at(edge.first), new_path});
                    visited.insert(edge.first);
                 }
            }
        }
        if(candidates.empty()) return {{}, -1};
        std::sort(candidates.begin(), candidates.end());
        beam.clear();
        for(int i = 0; i < std::min((int)candidates.size(), beam_width); ++i){
            beam.push_back(candidates[i].second);
        }
    }
}

int main() {
    int beam_width = 2;
    PathResult result = beam_search_history(graph, heuristics, START_NODE, GOAL_NODE, beam_width);
    print_result("Beam Search with History (Width=2)", result);
    return 0;
}
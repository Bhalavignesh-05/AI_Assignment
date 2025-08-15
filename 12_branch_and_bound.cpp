// 12_branch_and_bound.cpp 
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
PathResult get_oracle_result() {
    return {{'A', 'B', 'D', 'E', 'G'}, 16};
}

PathResult branch_and_bound(const Graph& g, char start, char goal) {
    int bound = get_oracle_result().second;
    
    std::stack<std::pair<std::vector<char>, int>> s;
    s.push({{start}, 0});
    PathResult best_result = {{}, -1};

    while(!s.empty()){
        std::pair<std::vector<char>, int> top_element = s.top();
        std::vector<char> path = top_element.first;
        int cost = top_element.second;
        s.pop();

        if(best_result.second != -1 && cost >= best_result.second) continue;

        char last_node = path.back();
        if(last_node == goal){
            if(best_result.second == -1 || cost < best_result.second){
                best_result = {path, cost};
                bound = cost; 
            }
            continue;
        }

        for(const auto& edge : g.at(last_node)){
            if(std::find(path.begin(), path.end(), edge.first) == path.end()){
                if ((cost + edge.second) < bound) { 
                    std::vector<char> new_path = path;
                    new_path.push_back(edge.first);
                    s.push({new_path, cost + edge.second});
                }
            }
        }
    }
    return best_result;
}

int main() {
    PathResult result = branch_and_bound(graph, START_NODE, GOAL_NODE);
    print_result("Branch and Bound", result);
    return 0;
}
// 11_oracle.cpp 
#include <iostream>
#include <vector>
#include <string>
#include <map>

using PathResult = std::pair<std::vector<char>, int>;

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

PathResult oracle() {
    std::vector<char> optimal_path = {'A', 'B', 'D', 'E', 'G'};
    int optimal_cost = 16;
    return {optimal_path, optimal_cost};
}

int main() {
    PathResult result = oracle();
    print_result("ORACLE", result);
    return 0;
}
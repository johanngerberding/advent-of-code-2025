#include <fstream>
#include <iostream> 
#include <vector>
#include <string> 
#include <sstream>


int main() {
    std::string filename = "input.txt";
    std::ifstream file(filename);
    std::string line;
    std::vector<std::vector<int>> grid;
    std::vector<char> symbols; 
    std::string last_line; 
    while(std::getline(file, line)) {
        if (!line.empty()) {
            last_line = line; 
            std::istringstream iss(line);
            std::vector<int> line_numbers;
            int num;
            if (iss >> num) {
                line_numbers.push_back(num);
                while (iss >> num) {
                    line_numbers.push_back(num);
                }
                grid.push_back(line_numbers);
            }
        }
    }
    char symbol; 
    std::istringstream last(last_line); 
    while (last >> symbol) {
        symbols.push_back(symbol);
    }
    file.close();
    // for (char c: symbols) {
    //     std::cout << c << " ";
    // }
    // std::cout << std::endl;
    // for (std::vector<int> vec: grid) {
    //     for (int n: vec) {
    //         std::cout << n << " ";
    //     } 
    //     std::cout << std::endl;
    // }
    long long result {0};
    char operand;
    for (int col = 0; col < symbols.size(); col++) {
        operand = symbols[col];
        long long line_result; 
        if (operand == '+') {
            line_result = 0;
        } else {
            line_result = 1;
        }    
        for (int row = 0; row < grid.size(); row++) {
            if (operand == '+') {
                line_result += grid[row][col];
            } else if (operand == '*') {
                line_result *= grid[row][col];
            } 
        }
        result += line_result;
    }
    std::cout << "Part 1: " << result << std::endl;
    return 0;
}
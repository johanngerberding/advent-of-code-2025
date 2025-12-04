#include <iostream> 
#include <fstream> 
#include <vector> 
#include <string> 
#include <tuple>


void loadGrid(std::string filename, std::vector<std::vector<char>>& grid) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        throw std::runtime_error("Failed to open file: " + filename);
    }
    std::string line;
    while (std::getline(file, line)) {
        std::vector<char> row;
        if (!line.empty()) {
            for (char c: line) {
                row.push_back(c);
            }
        }
        grid.push_back(row);
    }
    file.close();
} 

bool accessiblePaper(std::vector<std::vector<char>>& grid, int row, int col) {
    if (grid[row][col] != '@') {return false;}
    int adj {0};
    int max_row_len = grid[0].size();
    int max_col_len = grid.size();
    // up  
    if (row - 1 >= 0) {
        if (grid[row -1][col] == '@') {adj++;}
    }
    // up - right 
    if (row - 1 >= 0 && col + 1 < max_col_len) {
        if (grid[row - 1][col + 1] == '@') {adj++;}
    } 
    // right
    if (col + 1 < max_col_len) {
        if (grid[row][col + 1] == '@') {adj++;}
    }
    // down - right 
    if (row + 1 < max_row_len && col + 1 < max_col_len) {
        if (grid[row + 1][col + 1] == '@') {adj++;}
    }
    // down 
    if (row + 1 < max_row_len) {
        if (grid[row + 1][col] == '@') {adj++;}
    }
    // down left 
    if (row + 1 < max_row_len && col - 1 >= 0) {
        if (grid[row + 1][col - 1] == '@') {adj++;}
    }
    // left 
    if (col - 1 >= 0) {
        if (grid[row][col - 1] == '@') {adj++;}
    }
    // up left 
    if (row - 1 >= 0 && col - 1 >= 0) {
        if (grid[row - 1][col - 1] == '@') {adj++;}
    }
    if (adj < 4) {
        std::cout << row << "/" << col << std::endl;
        return true;
    } 
    return false;
}

int main() {
    
    std::vector<std::vector<char>> grid; 
    loadGrid("input.txt", grid);
    int part1{0}; 

    for (int row = 0; row < grid.size(); row++) {
        for (int col = 0; col < grid[row].size(); col++) {
            if (accessiblePaper(grid, row, col)) {part1++;}
        }
    } 
    std::cout << "Part 1: " << part1 << std::endl;
    return 0;
}
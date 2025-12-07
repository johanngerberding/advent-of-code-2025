#include <fstream>
#include <iostream> 
#include <vector>
#include <string> 
#include <sstream>
#include <algorithm> 


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

    std::ifstream file2(filename); 
    std::vector<std::string> input;  // Each string is a row
    while(std::getline(file2, line)) {
        input.push_back(line);
    } 
    
    int num_cols = input[0].length();   
    std::vector<int> separator_idxs; 

    for (int col = 0; col < num_cols; col++) {
        bool all_spaces = true;
        for (int row = 0; row < input.size(); row++) {
            if (input[row][col] != ' ') {
                all_spaces = false;
                break;
            } 
        }
        if (all_spaces) {
            separator_idxs.push_back(col);
        }
    }

    std::cout << "Separator col idxs:" << std::endl;
    for (int s: separator_idxs) {
        std::cout << s << std::endl;
    }

    std::cout << "columns:" << std::endl;
    std::vector<std::vector<std::string>> columns; 
    int last_idx {-1};
    for (int s: separator_idxs) {
        std::vector<std::string> column;
        for (std::string line: input) {
            column.push_back(line.substr(last_idx + 1, s - last_idx));
        }
        for (std::string r: column) {
            std::cout << r << std::endl;
        }
        columns.push_back(column);
        last_idx = s;
    }

    std::vector<std::string> column;
    for (std::string line: input) {
        column.push_back(line.substr(last_idx + 1));
    }
    for (std::string r: column) {
        std::cout << r << std::endl;
    }
    columns.push_back(column);

    long long part2 {0};
    for (std::vector<std::string> col: columns) {
        std::string last = col.back();
        col.pop_back();
        char op; 
        int col_result;
        if (std::find(last.begin(), last.end(), '+') != last.end()) {
            op = '+';
            col_result = 0;
        } else if (std::find(last.begin(), last.end(), '*') != last.end()) {
            op = '*';
            col_result = 1;
        } else {
            std::cout << "there is something wrong with the last column";
        }
        std::cout << "Operand: " << op << std::endl;

        int value;
        for (int i = col[0].length() - 1; i >= 0; i--) {
            std::string str_value; 
            for (std::string row: col) {
                str_value += row[i];
            }
            
            if (str_value.find_first_not_of(' ') == std::string::npos) {
                continue;
            } else {
                std::cout << "STR VALUE: " << str_value << std::endl;
                value = std::stoi(str_value); 
                if (op == '*') {
                    col_result *= value;
                } else if (op == '+') {
                    col_result += value;
                }
            } 

        }
        std::cout << "COL RESULT: " << col_result << std::endl;
        part2 += col_result;
    }

    std::cout << "PART 2: " << part2 << std::endl;
    file2.close();

    return 0;
}
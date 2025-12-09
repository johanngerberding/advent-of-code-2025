#include <string> 
#include <fstream>
#include <vector> 
#include <iostream> 
#include <set> 


int main() {
    std::string filename = "input.txt";
    std::ifstream file(filename);
    std::string line;
    std::vector<std::string> lines;  
    while (std::getline(file, line)) {
        lines.push_back(line);
    }
    file.close();

    std::set<int> indexes;
    int splits {0};

    for (std::string l: lines) {
        std::cout << l << std::endl; 
        if (indexes.empty()) {
            size_t idx = l.find('S');
            indexes.insert(static_cast<int>(idx));
        }
        size_t pos {0}; 
        std::set<int> splitters;
        while ((pos = l.find('^', pos)) != std::string::npos) {
            splitters.insert(static_cast<int>(pos));
            pos++;
        }

        std::set<int> new_indexes;  
        for (int sp: splitters) {
            int left;
            int right;
            if (indexes.find(sp) != indexes.end()) {
                left = sp - 1;
                right = sp + 1;
                indexes.erase(sp);
                new_indexes.insert(left);
                new_indexes.insert(right);
                splits++;
            }
        }
        if (!new_indexes.empty()) {
            indexes.insert(new_indexes.begin(), new_indexes.end());
        }
    }

    std::cout << "Part 1: " << splits << std::endl;

    return 0;
}
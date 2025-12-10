#include <string> 
#include <fstream>
#include <vector> 
#include <iostream> 
#include <set> 


int main() {
    std::string filename = "input_test.txt";
    std::ifstream file(filename);
    std::string line;
    std::vector<std::string> lines;  
    while (std::getline(file, line)) {
        lines.push_back(line);
    }
    file.close();

    std::set<int> indexes;
    int splits {0};

    std::vector<int> path;
    std::set<std::vector<int>> paths;

    for (std::string l: lines) {
        if (indexes.empty()) {
            int idx = static_cast<int>(l.find('S'));
            indexes.insert(idx);
            path.push_back(idx);
            paths.insert(path);
        }
        
        size_t pos {0}; 
        std::set<int> splitters;
        while ((pos = l.find('^', pos)) != std::string::npos) {
            splitters.insert(static_cast<int>(pos));
            pos++;
        }

        std::cout << "--------" << std::endl;
        for (std::vector<int> p: paths) {
            for (int i: p) {
                std::cout << i << " ";
            }
            std::cout << std::endl;
        }
    

        std::set<int> new_indexes;  
        std::set<std::vector<int>> new_paths;
        
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
                for (std::vector<int> p: paths) {
                    if (p.back() == sp) {
                        std::cout << p.back() << " == " << sp << std::endl;
                        std::vector<int> new_right(p);
                        std::vector<int> new_left(p);
                        new_right.push_back(right);
                        new_left.push_back(left);
                        new_paths.insert(new_right);
                        new_paths.insert(new_left);
                    }
                }
            }
        }

        if (!new_paths.empty()) {
            paths = new_paths;
        }

        if (!new_indexes.empty()) {
            indexes.insert(new_indexes.begin(), new_indexes.end());
        }
    }

    std::cout << "Part 1: " << splits << std::endl;
    std::cout << "Part 2: " << paths.size() << std::endl;
    return 0;
}
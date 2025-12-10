#include <string> 
#include <fstream>
#include <vector> 
#include <iostream> 
#include <set> 
#include <map>

int main() {
    std::string filename = "input.txt";
    std::ifstream file(filename);
    std::string line;
    std::vector<std::string> lines;  
    while (std::getline(file, line)) {
        lines.push_back(line);
    }
    file.close();

    // Track how many paths end at each index
    std::map<int, long long> position_paths;
    int splits = 0;

    for (const std::string& l: lines) {
        if (position_paths.empty()) {
            int idx = static_cast<int>(l.find('S'));
            position_paths[idx] = 1;
        }
        
        // Find all splitters in current line
        std::set<int> splitters;
        size_t pos = 0;
        while ((pos = l.find('^', pos)) != std::string::npos) {
            splitters.insert(static_cast<int>(pos));
            pos++;
        }

        std::map<int, long long> new_position_paths;
        
        for (const auto& [idx, count] : position_paths) {
            if (splitters.find(idx) != splitters.end()) {
                // This position splits
                int left = idx - 1;
                int right = idx + 1;
                new_position_paths[left] += count;
                new_position_paths[right] += count;
                splits++;
            } else {
                // This position doesn't split, carry forward
                new_position_paths[idx] += count;
            }
        }
        
        position_paths = std::move(new_position_paths);
    }

    long long total_paths = 0;
    for (const auto& [idx, count] : position_paths) {
        std::cout << idx << " - " << count << std::endl;
        total_paths += count;
    }

    std::cout << "Part 1: " << splits << std::endl;
    std::cout << "Part 2: " << total_paths << std::endl;
    return 0;
}
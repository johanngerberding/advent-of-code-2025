#include <iostream> 
#include <vector>
#include <string>
#include <stdexcept> 
#include <fstream> 
#include <sstream> 

std::vector<std::string> loadFromFile(const std::string& filename) {
    std::vector<std::string> lines;
    std::ifstream file(filename);

    if (!file.is_open()) {
        throw std::runtime_error("Failed to open file: " + filename);
    }

    std::string line; 
    while (std::getline(file, line)) {
        if (!line.empty()) {
            lines.push_back(line);
        }
    }

    file.close();
    return lines;
}


int countZeros(const std::vector<std::string>& rotations, int start) {
    int zeros {0};
    for (const auto& rotation: rotations) {
        int rot = std::stoi(rotation.substr(1));
        if (rotation[0] == 'L') {
            start -= rot;
            while (start < 0) {
                start = 99 + start + 1;
            }
        } else if (rotation[0] == 'R') {
            start += rot;
            while (start > 99) {
                start = start - 100;
            }
        } else {
            throw std::invalid_argument("Invalid first character in rotation " + rotation);            
        }

        // std::cout << start << std::endl;

        if (start == 0) {
            zeros++;
        }
    } 
    return zeros;
}

int main() {
    std::vector<std::string> test_rotations = {
        "L68", "L30", "R48", "L5", "R60", "L55", "L1", "L99", "R14", "L82"
    };
    int test_zeros = countZeros(test_rotations, 50);
    std::cout << "Test zero count: " << test_zeros << std::endl;
    std::vector<std::string> rotations = loadFromFile("input.txt");
    int zeros = countZeros(rotations, 50);
    std::cout << "Zero count: " << zeros << std::endl;
    return 0;
}
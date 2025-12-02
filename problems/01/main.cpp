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


int countZeros(const std::vector<std::string>& rotations, int start, int part) {
    int zeros {0};
    int overrun {0};
    for (const auto& rotation: rotations) {
        int rot = std::stoi(rotation.substr(1));
        if (rotation[0] == 'L') {
            if (rot > start) {
                if (start == 0) {
                    zeros--;
                } 
                start -= rot;
                while (start < 0) {
                    overrun++; 
                    if (part == 2) {
                        zeros++;
                    }
                    start = 100 + start;
                }
                if (start == 0) {
                    zeros++;
                }
            } else if (rot == start) {
                start = 0;
                zeros++;
            } else {
                start -= rot;
            }
            std::cout << rotation << " caused " << overrun << " overruns. curr: " << start << " zero count: " << zeros << std::endl;
        } else if (rotation[0] == 'R') {
            if (rot > (100 - start)) { 
                start += rot;
                while (start > 99) {
                    overrun++;
                    if (part == 2) {
                        zeros++;
                    }
                    start = start - 100;
                }
            } else if (rot == (100 - start)) {
                start = 0;
                zeros++;
            } else {
                start += rot;
            }
            std::cout << rotation << " caused " << overrun << " overruns. curr: " << start << " zero count: " << zeros << std::endl;
        } else {
            throw std::invalid_argument("Invalid first character in rotation " + rotation);            
        }

        overrun = 0;

    } 
    return zeros;
}

int main() {
    std::vector<std::string> test_rotations = {
        "L68", "L30", "R48", "L5", "R60", "L55", "L1", "L99", "R14", "L82"
    };
    // int test_zeros = countZeros(test_rotations, 50, 1);
    // std::cout << "Test zero count: " << test_zeros << std::endl;
    // std::vector<std::string> rotations = loadFromFile("input.txt");
    // int zeros = countZeros(rotations, 50, 1);
    // std::cout << "Zero count: " << zeros << std::endl;
    
    int test_zeros = countZeros(test_rotations, 50, 2);
    std::cout << "Part 2 zero count: " << test_zeros << std::endl;
    std::vector<std::string> rotations = loadFromFile("input.txt");
    int zeros = countZeros(rotations, 50, 2);
    std::cout << "Part 2 Zero count: " << zeros << std::endl;
   return 0;
}
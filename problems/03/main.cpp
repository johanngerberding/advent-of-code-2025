#include <iostream> 
#include <fstream> 
#include <sstream> 
#include <vector> 
#include <string> 
#include <stdexcept>
#include <algorithm> 
#include <numeric>


std::vector<std::vector<int>> loadFromFile(std::string filename) {
    std::vector<std::string> lines;
    std::vector<std::vector<int>> ids;
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

    for (const std::string line : lines) {
        std::vector<int> id_line;
        for (int i = 0; i < line.length(); i++) {
            id_line.push_back(std::stoi(std::string(1, line[i])));
        }
        ids.push_back(id_line);    
    }

    return ids;
}


long long buildNumber(std::vector<int> numbers, int n) {
    std::vector<int> batteries(numbers.begin(), numbers.begin() + n);

    for (size_t idx = 12; idx < numbers.size(); idx++) {
        int joltage = numbers[idx];

        bool inserted = false; 
        for (size_t i = 0; i < 11; ++i) {
            if (batteries[i] < batteries[i + 1]) {
                batteries.erase(batteries.begin() + i);
                batteries.push_back(joltage);
                inserted = true;
                break;
            } 
        }

        if (!inserted && joltage > batteries.back()) {
            batteries.back() = joltage;
        }
    }
    
    std::string result;
    for (int b: batteries) {
        result += std::to_string(b);
    }
    std::cout << result << std::endl; 
    return std::stoull(result);
}

int main() {
    std::string filename = "input.txt";
    std::vector<std::vector<int>> lines = loadFromFile(filename);
    // std::vector<int> results; 
    // int result;
    // for (std::vector<int> line : lines) {
    //     auto max_it = std::max_element(line.begin(), line.end()); 
    //     int maxValue = *max_it;

    //     int maxIndex = std::distance(line.begin(), max_it);
    //     int maxValue2;         

    //     // max element is last element
    //     if (maxIndex == (line.size() - 1)) {
    //         maxValue2 = maxValue; 
    //         max_it = std::max_element(line.begin(), line.end() - 1);
    //         maxValue = *max_it;
    //     } else {
    //         auto max2_it = std::max_element(max_it + 1, line.end());
    //         maxValue2 = *max2_it;
    //     } 
    //     std::cout << "Max value: " << maxValue << " second " << maxValue2 << std::endl;
    //     result = std::stoi((std::to_string(maxValue) + std::to_string(maxValue2)));
    //     results.push_back(result);
    // } 
    // int sum = std::accumulate(results.begin(), results.end(), 0);
    // std::cout << "Part 1: " << sum << std::endl;

    std::vector<unsigned long long> part2_numbers; 
    for (std::vector<int> line : lines) {
        part2_numbers.push_back(buildNumber(line, 12));
    }

    unsigned long long sum2 = std::accumulate(part2_numbers.begin(), part2_numbers.end(), 0LL);
    std::cout << "Part 2: " << sum2 << std::endl;

    return 0;
}
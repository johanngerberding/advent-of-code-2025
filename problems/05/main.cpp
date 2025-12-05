#include <fstream>
#include <iostream> 
#include <string> 


struct Range {
    long long start;
    long long end;
    
    Range (const std::string& str) {
        size_t pos = str.find('-');
        start = std::stoll(str.substr(0, pos));
        end = std::stoll(str.substr(pos + 1));
    }
    bool contains(long long value) { return value >= start && value <= end; }
};

std::ostream& operator<<(std::ostream& os, const Range& r) {
    os << "[" << r.start << "-" << r.end << "]";
    return os;
}

int main() {
    std::ifstream file("input.txt"); 
    std::string line;  
    std::vector<Range> ranges; 
    while (std::getline(file, line)) {
        if (!line.empty()) {
            ranges.push_back(Range(line));
        } else {
            break;
        } 
    }
    for (const Range& r: ranges) {
        std::cout << r << std::endl;
    }

    long long number;
    int part1 {0};
    while (std::getline(file, line)) {
        if (!line.empty()) {
            number = std::stoll(line);
            for (Range r: ranges) {
                if (r.contains(number)) {
                    part1++;
                    break;
                }
            }
        } else {
            break;
        } 
    }

    std::cout << "Part 1: " << part1 << std::endl;

    file.close();
    return 1;
}
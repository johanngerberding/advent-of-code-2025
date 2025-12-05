#include <fstream>
#include <iostream> 
#include <string> 
#include <set>
#include <algorithm> 


struct Range {
    long long start;
    long long end;
    
    Range (const std::string& str) {
        size_t pos = str.find('-');
        start = std::stoll(str.substr(0, pos));
        end = std::stoll(str.substr(pos + 1));
    }

    Range(long long s, long long e): start(s), end(e) {}

    bool contains(long long value) { return value >= start && value <= end; }
    
    bool overlaps(const Range& other) {
        return !(end < other.start - 1 || start > other.end + 1);
    }

    Range merge(const Range& other) {
        return Range(std::min(start, other.start), std::max(end, other.end));
    }

    long long length() { return end - start + 1; }

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
    
    std::sort(ranges.begin(), ranges.end(), 
        [](const Range& a, const Range& b) { return a.start < b.start; } 
    );
    
    for (Range r: ranges) {
        std::cout << r << std::endl;
    } 
    
    bool merged; 
    while (true) { 
        merged = false; 
        for (int i = 0; i < ranges.size() - 1; i++) {
            if (ranges[i].overlaps(ranges[i + 1])) {
                Range r = ranges[i].merge(ranges[i+1]);
                ranges.erase(ranges.begin() + i);
                ranges.erase(ranges.begin() + i);
                ranges.push_back(r);
                std::sort(ranges.begin(), ranges.end(), 
                    [](const Range& a, const Range& b) { return a.start < b.start; } 
                );
                merged = true;
                break;
            } else {
                continue;
            }
        }
        if (!merged) {break;}
    }

    long long part2 {0};
    for (Range r: ranges) {
        part2 += r.length();
        std::cout << r << std::endl;
    }

    std::cout << "Part 2: " << part2 << std::endl;

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
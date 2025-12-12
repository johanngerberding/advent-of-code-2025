#include <fstream> 
#include <iostream> 
#include <string> 
#include <vector> 
#include <algorithm> 


struct Point {
    long long x;
    long long  y;
};

Point parseLine(std::string& line) {
    Point p;
    size_t commaPos = line.find(',');
    p.x = std::stoll(line.substr(0, commaPos));
    p.y = std::stoll(line.substr(commaPos + 1));
    return p;
} 

long long calcArea(const Point& p1, const Point& p2) {
    if (p1.x <= p2.x && p1.y <= p2.y) {
        // p1 is upper left corner
        return (p2.y + 1 - p1.y) * (p2.x + 1 - p1.x);
    } else if (p1.x <= p2.x && p1.y >= p2.y) {
        // p1 is down left corner
        return (p1.y + 1 - p2.y) * (p2.x + 1 - p1.x);
    } else if (p1.x >= p2.x && p2.y >= p1.y) {
        // p1 is upper right corner
        return (p2.y + 1 - p1.y) * (p1.x + 1 - p2.x);
    } else {
        // p1 is down right corner
        return (p1.y + 1 - p2.y) * (p1.x + 1 - p2.x);
    }
}


int main() {
    std::ifstream file("input.txt");
    std::string line; 
    std::vector<Point> points;
    while (std::getline(file, line)) {
        points.push_back(parseLine(line));
    }
    file.close();
    std::cout << "Parsed input file" << std::endl;
    Point p1;
    Point p2;
    std::vector<long long> areas;
    long long area;

    std::cout << "Number of points: " << points.size() << std::endl;
    for (int i = 0; i < points.size() - 1; i++) {
        p1 = points[i];
        for (int k = i + 1; k < points.size(); k++) {
            p2 = points[k];
            if (!(p1.x == p2.x && p1.y == p2.y)) {
                area = calcArea(p1, p2);
                areas.push_back(area);
            } 
        }
    }

    std::sort(areas.begin(), areas.end(), std::greater<long long>());
    std::cout << "Part 1: " << areas[0] << std::endl;

    return 0;
}
#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <cmath>


struct Junction {
    int X;
    int Y;
    int Z;
};

Junction parseJunction(const std::string& line) {
    Junction j;
    std::istringstream ss(line);
    char comma;
    ss >> j.X >> comma >> j.Y >> comma >> j.Z;
    return j;
}

double distance(const Junction& j1, const Junction& j2) {
    int dx = j1.X - j2.X;
    int dy = j1.Y - j2.Y;
    int dz = j1.Z - j2.Z;
    return std::sqrt(dx*dx + dy*dy + dz*dz);
}


int main() {
    std::ifstream file("input_test.txt");
    std::string line; 
    std::vector<Junction> junctions; 
    while (std::getline(file, line)) {
        junctions.push_back(parseJunction(line));
    }
    file.close(); 

    for (const auto& j: junctions) {
        std::cout << "X: " << j.X << ", Y: " << j.Y << ", Z: " << j.Z << std::endl;
    }

    return 0;
}
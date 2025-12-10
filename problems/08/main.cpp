#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <cmath>
#include <map> 
#include <set> 


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
    
    size_t n = junctions.size();
    std::vector<std::vector<double>> distances(n, std::vector<double>(n, 0.0));  
    for (size_t i = 0; i < n; ++i) {
        for (size_t j = 0; j < n; ++j) {
            distances[i][j] = distance(junctions[i], junctions[j]);
        }
    }
    
    std::vector<std::set<int>> circuits; 
    std::set<std::pair<int, int>> done;

    for (int round = 0; round < 10; round++) {
        int min_i {-1};
        int min_j {-1};
        double min_distance {10000.0}; 
        for (size_t i = 0; i < n; ++i) {
            for (size_t j = 0; j < n; ++j) {
                if (i != j && done.find(std::pair(i, j)) == done.end()) {
                    if (distances[i][j] < min_distance) {
                        min_distance = distances[i][j];
                        min_i = i;
                        min_j = j;
                    }
                } 
            }
        }
        std::set<int> circuit; 
        bool found = false;
        if (circuits.empty()) {
            circuit.insert(min_i);
            circuit.insert(min_j);
        } else {
            
            for (std::set<int> c: circuits) {
                if (c.find(min_i) != c.end() || c.find(min_j) != c.end()) {
                    c.insert(min_i);
                    c.insert(min_j);
                    found = true;
                }
            }
            if (!found) {
                circuit.insert(min_i);
                circuit.insert(min_j);
                circuits.push_back(circuit);
            }
        }
        done.insert(std::pair(min_i, min_j));
    }

    for (std::set<int> c: circuits) {
        std::cout << " circuit: "; 
        for (int idx: c) {
            std::cout << idx << " ";
        }
        std::cout << std::endl;
    } 

    return 0;
}

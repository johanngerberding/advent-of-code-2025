#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <cmath>
#include <map> 
#include <set> 
#include <algorithm>


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
    std::ifstream file("input.txt");  // Use test input first
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

    int connections_made = 0;
    int round = 0;

    while (connections_made < 999) {
        int min_i {-1};
        int min_j {-1};
        double min_distance {1000000000.0}; 
        for (size_t i = 0; i < n; ++i) {
            for (size_t j = 0; j < n; ++j) {
                if (i != j && done.find({i, j}) == done.end()) {
                    if (distances[i][j] < min_distance) {
                        min_distance = distances[i][j];
                        min_i = i;
                        min_j = j;
                    }
                } 
            }
        }
        
        // std::cout << "Round " << round << ": Connecting " << min_i << " and " << min_j 
        //         << " (distance: " << min_distance << ")" << std::endl;
        
        std::set<int> circuit;
        bool found = false;
        bool actually_connected = false;  // Track if we made an actual connection
        
        if (circuits.empty()) {
            circuit.insert(min_i);
            circuit.insert(min_j);
            circuits.push_back(circuit);
            actually_connected = true;
        } else {
            int index_min_i = -1;
            int index_min_j = -1;
            for (size_t idx = 0; idx < circuits.size(); idx++) {
                if (circuits[idx].find(min_i) != circuits[idx].end()) {
                    index_min_i = idx; 
                    found = true;
                }  
                if (circuits[idx].find(min_j) != circuits[idx].end()) {
                    index_min_j = idx; 
                    found = true;
                }
            }
            
            if (found) {
                if (index_min_i != -1 && index_min_j != -1) {
                    if (index_min_i != index_min_j) {
                        // std::cout << "  Merging circuits " << index_min_i << " and " << index_min_j << std::endl;
                        std::set<int> combined = circuits[index_min_i];
                        combined.insert(circuits[index_min_j].begin(), circuits[index_min_j].end());
                        combined.insert(min_i);
                        combined.insert(min_j);
                        int first = std::min(index_min_i, index_min_j);
                        int second = std::max(index_min_i, index_min_j);
                        circuits.erase(circuits.begin() + second);
                        circuits.erase(circuits.begin() + first);
                        circuits.push_back(combined);
                        actually_connected = true;
                    } else {
                        // std::cout << "  Both already in same circuit " << index_min_i << " - no connection made" << std::endl;
                        actually_connected = false;  // No actual connection
                    }
                } else if (index_min_i != -1) {
                    // std::cout << "  Adding to circuit " << index_min_i << std::endl;
                    circuits[index_min_i].insert(min_i);
                    circuits[index_min_i].insert(min_j);
                    actually_connected = true;
                } else if (index_min_j != -1) {
                    // std::cout << "  Adding to circuit " << index_min_j << std::endl;
                    circuits[index_min_j].insert(min_i);
                    circuits[index_min_j].insert(min_j);
                    actually_connected = true;
                }
            } else {
                // std::cout << "  Creating new circuit" << std::endl;
                circuit.insert(min_i);
                circuit.insert(min_j);
                circuits.push_back(circuit);
                actually_connected = true;
            }
        }
        
        done.insert({min_i, min_j});
        done.insert({min_j, min_i});
        
        if (actually_connected) {
            connections_made++;
        }
        round++;
        std::cout << "Connections: " << connections_made << std::endl;
    }

    std::cout << "\nFinal circuits:" << std::endl;
    std::vector<int> circuit_lengths; 
    for (size_t i = 0; i < circuits.size(); i++) {
        std::cout << "Circuit " << i << " (size " << circuits[i].size() << "): ";
        for (int idx: circuits[i]) {
            std::cout << idx << " ";
        }
        std::cout << std::endl;
        circuit_lengths.push_back(circuits[i].size());
    } 
    std::sort(circuit_lengths.begin(), circuit_lengths.end(), std::greater<int>());
    
    std::cout << "\nSorted circuit sizes: ";
    for (int size : circuit_lengths) {
        std::cout << size << " ";
    }
    std::cout << std::endl;
    
    long long part1 {0}; 
    if (circuit_lengths.size() >= 3) { 
        part1 = (long long)circuit_lengths[0] * circuit_lengths[1] * circuit_lengths[2];
    }
    std::cout << "Part 1: " << part1 << std::endl;
    return 0;
}
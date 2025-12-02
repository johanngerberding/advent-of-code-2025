#include <iostream> 
#include <sstream> 
#include <fstream> 

std::string loadFromFile(const std::string& filename) {
    std::ifstream file(filename);

    if (!file.is_open()) {
        throw std::runtime_error("Failed to open file: " + filename);
    }

    std::string line; 
    std::getline(file, line);
    file.close();
    return line;
}

std::vector<std::string> split(const std::string& str, char sep) {
    std::vector<std::string> tokens; 
    std::stringstream ss(str);
    std::string token; 

    while (std::getline(ss, token, sep)) {
        tokens.push_back(token);
    }
    return tokens;
}

int main() {
    
    std::string filename = "input.txt";
    std::string ids = loadFromFile(filename);    
    std::cout << ids << std::endl;

    std::vector<std::string> tokens = split(ids, ',');

    return 0;
}
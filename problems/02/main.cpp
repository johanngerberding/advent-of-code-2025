#include <iostream> 
#include <sstream> 
#include <fstream> 
#include <vector> 
#include <string> 
#include <tuple> 
#include <numeric> 


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

bool check_number(long long n) {
    std::string id_str = std::to_string(n);
    if (id_str.length() % 2 > 0) return false;  
    size_t mid = id_str.length() / 2; 
    std::string first_half = id_str.substr(0, mid);
    std::string second_half = id_str.substr(mid);
    if (first_half == second_half) return true;
    return false; 
}

int main() {
    
    std::string filename = "input.txt";
    std::string ids = loadFromFile(filename);    
    std::cout << ids << std::endl;

    std::vector<std::string> tokens = split(ids, ',');
    std::vector<long long> numbers; 
    // parse first and second id 
    for (const std::string& token : tokens) {
        std::vector<std::string> first_last_id = split(token, '-');
        long long first_id = std::stoll(first_last_id[0]);
        long long last_id = std::stoll(first_last_id[1]);

        for (long long id = first_id; id <= last_id; id++) {
            if (check_number(id)) {
                numbers.push_back(id);
            }
        }
    }
    
    long long sum = std::accumulate(numbers.begin(), numbers.end(), 0LL);    
    std::cout << sum << std::endl;
    return 0;
}
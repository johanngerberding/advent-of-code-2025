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


std::vector<std::string> create_parts(std::string id_str, int part_length, int num_parts) {
    std::vector<std::string> parts; 
    for (int i = 0; i < num_parts; i++) {
        parts.push_back(id_str.substr(i * part_length, (i + 1) * part_length));
    }
    return parts;
}


bool check_number_2(long long n) {
    std::string id_str = std::to_string(n);
    int len = id_str.length();
    for (int num_parts = 2; num_parts <= len; num_parts++) 
    {
        if (len % num_parts == 0) 
        {
            int part_length = len / num_parts;
            std::string frist_part = id_str.substr(0, part_length);

            bool all_equal = true; 
            for (int i = 1; i < num_parts; i++) {
                std::string part = id_str.substr(i * part_length, part_length);
                if (part != frist_part)
                {
                    all_equal = false;
                    break;
                }
            }
            if (all_equal) return true;
        }
    }
    return false; 
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
    std::vector<long long> numbers_2; 
    // parse first and second id 
    for (const std::string& token : tokens) {
        std::vector<std::string> first_last_id = split(token, '-');
        long long first_id = std::stoll(first_last_id[0]);
        long long last_id = std::stoll(first_last_id[1]);

        for (long long id = first_id; id <= last_id; id++) {
            if (check_number(id)) {
                numbers.push_back(id);
            }
            if (check_number_2(id)) {
                numbers_2.push_back(id);
            }
        }
    }
    
    long long sum = std::accumulate(numbers.begin(), numbers.end(), 0LL);    
    std::cout << "Part 1: " << sum << std::endl;
    long long sum2 = std::accumulate(numbers_2.begin(), numbers_2.end(), 0LL);    
    std::cout << "Part 2: " << sum2 << std::endl;
    return 0;
}
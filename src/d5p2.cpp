#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include <iterator>
#include <array>

inline
bool can_react(const char &first, const char &second) {
    return toupper(first) == toupper(second) && first != second;
}

std::string react(const std::string &input) {
    for (unsigned i = 0; i < input.size() - 1; ++i) {
        if (can_react(input[i], input[i + 1])) {
            std::string reacted = input.substr(0, i);
            reacted.append(input.substr(i + 2));
            return react(reacted);
        }
    }
    return input;
}

int main() {
    std::ifstream ifs("../data/d5input");
    if (!ifs) {
        std::cerr << "Unable to open input file" << std::endl;
        return -1;
    }

    std::string input;
    std::getline(ifs, input);
    std::array<unsigned, 26> polymer_length = {};
    for (char c = 'a'; c <= 'z'; ++c) {
        std::string without_this_type;
        std::remove_copy_if(input.cbegin(), input.cend(), std::back_inserter(without_this_type), [&c] (char cc) {
            return cc == c || cc == toupper(c); });
        std::string output = react(without_this_type);
        polymer_length[c - 'a'] = output.length();
    }
    
    unsigned shortest_length = -1;
    for (unsigned i = 0; i < 26; ++i) {
        if (polymer_length[i] < shortest_length) {
            shortest_length = polymer_length[i];
        }
    }
    std::cout << shortest_length << std::endl;
    return 0;
}
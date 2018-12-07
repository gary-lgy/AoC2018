#include <iostream>
#include <fstream>
#include <string>

inline
bool can_react(const char &first, const char &second) {
    return toupper(first) == toupper(second) && first != second;
}

std::string react(const std::string &input) {
    for (unsigned i = 0; i < input.size() - 1; ++i) {
        if (can_react(input[i], input[i + 1])) {
            std::string temp = input.substr(0, i);
            temp.append(input.substr(i + 2));
            return react(temp);
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
    std::string output = react(input);
    std::cout << output << std::endl;
    std::cout << output.size() << std::endl;
    return 0;
}
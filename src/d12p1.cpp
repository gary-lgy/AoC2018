#include <iostream>
#include <fstream>
#include <string>
#include <map>

int main() {
    std::ifstream ifs("../data/d12input");
    if (!ifs) {
        std::cerr << "Unable to open input file" << std::endl;
        return -1;
    }

    std::string state;
    ifs >> state >> state >> state;
    std::string cond;
    char result;
    std::map<std::string, char> rules;
    while (ifs >> cond) {
        ifs >> result >> result >> result;
        rules.insert({cond, result});
    }
    ifs.close();
    
    state = std::string(30, '.') + state + std::string(30, '.');
    for (int g = 0; g < 20; ++g) {
        std::string old_state = state;
        for (int i = 2; i < state.size() - 2; ++i) {
            state[i] = rules.at(old_state.substr(i - 2, 5));
        }
    }

    int answer = 0;
    for (int i = 0; i < state.size(); ++i) {
        if (state[i] == '#') {
            answer += i - 30;
        }
    }
    std::cout << answer << std::endl;
    return 0;
}
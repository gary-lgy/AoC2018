#include <iostream>
#include <fstream>
#include <string>
#include <map>

const long GENERATIONS = 200;
const long VIEW_LIMIT = 3000;

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
    
    state = std::string(VIEW_LIMIT, '.') + state + std::string(VIEW_LIMIT, '.');
    for (long g = 1; g <= GENERATIONS; ++g) {
        std::string old_state = state;
        for (long long i = 2; i < state.size() - 2; ++i) {
            state[i] = rules.at(old_state.substr(i - 2, 5));
        }
        long long answer = 0;
        for (long long i = 0; i < state.size(); ++i) {
            if (state[i] == '#') {
                answer += i - VIEW_LIMIT;
            }
        }
        std::cout << g <<  " " << answer << std::endl;
    }

    // by inspection, the difference between two consecutive generations from the 101st generation (6767) onwards is always 67
    // therefore after 50000000000 generations, the sum will be
    std::cout << "50000000000 " << 6767 + (50000000000 - 101) * static_cast<long long>(67) << std::endl;
    return 0;
}
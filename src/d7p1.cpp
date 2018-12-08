#include <iostream>
#include <fstream>
#include <string>
#include <set>
#include <vector>
#include <algorithm>
#include <utility>

bool can_be_done(const char &c, const std::vector<std::vector<int>> &graph, const std::set<char> &done) {
    for (int i = 0; i < 26; ++i) {
        if (graph[i][c - 'A'] == 1 && done.find(i + 'A') == done.end()) {
            return false;
        }
    }
    return true;
}

int main() {
    std::ifstream ifs("../data/d7input");
    if (!ifs) {
        std::cerr << "Unable to open input file" << std::endl;
        return -1;
    }

    // use adjacency matrix to represent the graph
    std::vector<std::vector<int>> graph(26, std::vector<int>(26, -1));
    std::set<char> steps;
    std::string line;
    while (std::getline(ifs, line)) {
        auto temp = std::find_if(line.begin() + 1, line.end(), isupper);
        char origin = *temp, dest = *std::find_if(temp + 1, line.end(), isupper);
        graph[origin - 'A'][dest - 'A'] = 1;
        steps.insert(origin);
        steps.insert(dest);
    }

    // initialization (add all steps without prerequisites as candidates)
    std::set<char> done;
    std::set<char> candidates;
    for (const auto &step : steps) {
        if (can_be_done(step, graph, done)) {
            candidates.insert(step);
        }
    }

    // add steps
    std::string answer;
    while (!candidates.empty()) {
        char pos = *std::find_if(candidates.begin(), candidates.end(), [&graph, &done] (const char &step) {
            return can_be_done(step, graph, done);
        });
        done.insert(pos);
        answer.push_back(pos);
        candidates.erase(pos);
        for (const auto &step : steps) {
            if (graph[pos - 'A'][step - 'A'] == 1) {
                candidates.insert(step);
            }
        }
    }

    std::cout << answer << std::endl;
    return 0;
}
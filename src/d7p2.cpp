#include <iostream>
#include <fstream>
#include <string>
#include <set>
#include <vector>
#include <algorithm>
#include <utility>
#include <iterator>

const int NUMBER_OF_WORKERS = 5;
const int BASE_TIME = 60;

bool can_be_done(const char &c, const std::vector<std::vector<int>> &graph, const std::set<char> &done) {
    for (int i = 0; i < 26; ++i) {
        if (graph[i][c - 'A'] == 1 && done.find(i + 'A') == done.end()) {
            return false;
        }
    }
    return true;
}

void progress_time(std::vector<std::pair<char, int>> &time_left) {
    for (int i = 0; i < time_left.size(); ++i) {
        if (time_left[i].second != -1) {
            --time_left[i].second;
        }
    }
}

void check_done_steps(std::vector<std::pair<char, int>> &time_left, std::set<char> &done,
                      std::set<char> &candidates, const std::vector<std::vector<int>> &graph) {
    for (int i = 0; i < time_left.size(); ++i) {
        if (time_left[i].second == 0) {
            char done_step = time_left[i].first;
            done.insert(done_step);
            time_left[i].second = -1;
            time_left[i].first = '*';
            for (int ii = 0; ii != 26; ++ii) {
                if (graph[done_step - 'A'][ii] == 1) {
                    candidates.insert(static_cast<char>(ii + 'A'));
                }
            }
        }
    }
}

void allocate_steps(std::vector<std::pair<char, int>> &time_left, std::set<char> &available_steps, std::set<char> &candidates) {
    int idle_workers = std::count_if(time_left.begin(), time_left.end(), [] (const std::pair<char, int> &p) {
        return p.second == -1;
    });
    int current_step_cnt = idle_workers < available_steps.size() ? idle_workers : available_steps.size();
    for (int i = 0; current_step_cnt != 0; ++i) {
        if (time_left[i].second == -1) {
            char current_step = *available_steps.begin();
            available_steps.erase(current_step);
            candidates.erase(current_step);
            time_left[i].first = current_step;
            time_left[i].second = BASE_TIME + 1 + current_step - 'A';
            --current_step_cnt;
        }
    }
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

    // allocate steps to each worker
    /* debug */ std::cout << "Second\tWorker1\tWorker2\tDone\t" << std::endl;
    std::vector<std::pair<char, int>> time_left(NUMBER_OF_WORKERS, { '*', -1 }); // worker no. -> { step, time left til done }
    int time_elapsed = 0;
    while (done.size() != steps.size()) {
        progress_time(time_left);
        check_done_steps(time_left, done, candidates, graph);
        std::set<char> available_steps;
        std::copy_if(candidates.begin(), candidates.end(), std::inserter(available_steps, available_steps.begin()), [&graph, &done] (const char &step) {
            return can_be_done(step, graph, done);
        });
        allocate_steps(time_left, available_steps, candidates);
        /* debug */ std::cout << time_elapsed << "\t";
        /* debug */ for (auto &w : time_left) {
        /* debug */     std::cout << w.first << "\t";
        /* debug */ }
        /* debug */ for (auto &w : done) {
        /* debug */     std::cout << w;
        /* debug */ }
        /* debug */ std::cout << std::endl;
        ++time_elapsed;
    }

    return 0;
}
#include <iostream>
#include <fstream>
#include <sstream>
#include <unordered_map>
#include <array>
#include <vector>
#include <algorithm>
#include <string>

struct Time {
    std::array<unsigned short, 5> data;
};

struct Record {
    Time time;
    std::string activity;
};

// for sorting the records
bool operator<(const Record &lhs, const Record &rhs) {
    if (lhs.time.data < rhs.time.data) {
        return true;
    } else if (lhs.time.data == rhs.time.data) {
        return lhs.activity.length() > rhs.activity.length();
    } else {
        return false;
    }
}

int main() {
    std::ifstream ifs("../data/d4input");
    if (!ifs) {
        std::cerr << "Unable to open input file" << std::endl;
        return -1;
    }
    // read records from input file
    std::vector<Record> records;
    std::string line;
    while (std::getline(ifs, line)) {
        std::transform(line.begin(), line.end(), line.begin(), [](const char &c) {
            return c == '-' || c == '[' || c == ']' || c == ':' ? ' ' : c; });
        std::stringstream line_str(line);
        Record record;
        line_str >> record.time.data[0] >> record.time.data[1] >> record.time.data[2] >> record.time.data[3] >> record.time.data[4];
        line_str >> std::ws;
        std::getline(line_str, record.activity);
        records.push_back(record);
    }
    // sort the records in chronological order
    std::sort(records.begin(), records.end());
    // build sleep_graph for each guard
    std::unordered_map<unsigned, std::array<unsigned, 60>> sleep_graph;
    unsigned curr_guard_id = -1;
    unsigned last_asleep_minute = -1;
    for (auto &record : records) {
        if (record.activity[0] == 'G') {
            curr_guard_id = std::stoul(record.activity.substr(7));
        } else if (record.activity[0] == 'f') {
            last_asleep_minute = record.time.data[4];
        } else if (record.activity[0] == 'w') {
            unsigned wake_minute = record.time.data[4];
            if (sleep_graph.find(curr_guard_id) == sleep_graph.end()) {
                sleep_graph.insert({curr_guard_id, std::array<unsigned, 60>{}});
            }
            auto &curr_sleep_graph = sleep_graph[curr_guard_id];
            for (unsigned i = last_asleep_minute; i < wake_minute; ++i) {
                ++curr_sleep_graph[i];
            }
        }
    }
    // find the guard with the most minutes asleep
    unsigned most_sleepy_guard_id = -1;
    unsigned longest_duration_asleep = 0;
    for (auto beg = sleep_graph.cbegin(); beg != sleep_graph.cend(); ++beg) {
        unsigned asleep_duration = std::accumulate(beg->second.begin(), beg->second.end(), 0,
                                                   [] (unsigned acc, unsigned count) { return acc + count; });
        if (asleep_duration > longest_duration_asleep) {
            longest_duration_asleep = asleep_duration;
            most_sleepy_guard_id = beg->first;
        }
    }
    // find the minute that the said guard spends asleep most
    auto &most_sleepy_sleep_graph = sleep_graph[most_sleepy_guard_id];
    unsigned most_sleepy_minute = std::max_element(most_sleepy_sleep_graph.begin(), most_sleepy_sleep_graph.end()) - most_sleepy_sleep_graph.begin();

    // print the result
    std::cout << "Most sleepy guard: " + std::to_string(most_sleepy_guard_id) << std:: endl;
    std::cout << "Most sleepy minute: " + std::to_string(most_sleepy_minute) << std:: endl;
    std::cout << most_sleepy_guard_id * most_sleepy_minute << std::endl;
}
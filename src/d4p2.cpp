#include <iostream>
#include <fstream>
#include <sstream>
#include <unordered_map>
#include <array>
#include <vector>
#include <algorithm>
#include <string>
#include <utility>

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
    // find the minute that each guard spend the most asleep
    std::unordered_map<unsigned, std::pair<unsigned short, unsigned>> most_sleepy_minute_table; // guard_id -> { minute, count }
    for (auto beg = sleep_graph.cbegin(); beg != sleep_graph.cend(); ++beg) {
        auto most_sleepy_minute_pos = std::max_element(beg->second.begin(), beg->second.end());
        unsigned short most_sleepy_minute = most_sleepy_minute_pos - beg->second.begin();
        unsigned sleep_count = *most_sleepy_minute_pos;
        most_sleepy_minute_table[beg->first] = { most_sleepy_minute, sleep_count };
    }
    // find which guard has the highest sleep count for some minute
    unsigned most_sleepy_guard_id = -1;
    unsigned highest_sleep_count = 0;
    for (auto beg = most_sleepy_minute_table.begin(); beg != most_sleepy_minute_table.end(); ++beg) {
        unsigned curr_sleep_count = beg->second.second;
        if (curr_sleep_count > highest_sleep_count) {
            highest_sleep_count = curr_sleep_count;
            most_sleepy_guard_id = beg->first;
        }
    }
    // print the result
    auto answer_minute = most_sleepy_minute_table[most_sleepy_guard_id].first;
    std::cout << "Most sleepy guard: " + std::to_string(most_sleepy_guard_id) << std:: endl;
    std::cout << "Sleep count: " + std::to_string(highest_sleep_count) << std:: endl;
    std::cout << "Corresponding minute: " + std::to_string(answer_minute) << std:: endl;
    std::cout << most_sleepy_guard_id * answer_minute << std::endl;
}

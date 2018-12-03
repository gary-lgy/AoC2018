#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

int main() {
    std::fstream ifs("../data/d2input");
    if (!ifs) {
        std::cerr << "Unable to open input file" << std::endl;
        return -1;
    }
    unsigned two_count = 0, three_count = 0;
    std::string curr_item;
    while (std::getline(ifs, curr_item)) {
        std::vector<unsigned> char_count(26, 0);
        for (auto &c : curr_item) {
            ++char_count[c - 97];
        }
        if (std::find(char_count.begin(), char_count.end(), 2) != char_count.end()) {
            ++two_count;
        }
        if (std::find(char_count.begin(), char_count.end(), 3) != char_count.end()) {
            ++three_count;
        }
    }
    std::cout << two_count * three_count << std::endl;
    return 0;
}
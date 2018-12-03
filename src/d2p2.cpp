#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <utility>

bool differ_by_one(const std::string &lhs, const std::string &rhs) {
    unsigned differ_count = 0;
    for (unsigned i = 0; i < lhs.size(); ++i) {
       if (lhs[i] != rhs[i]) {
            ++differ_count;
       } 
    }
    return differ_count == 1;
}

std::pair<unsigned, unsigned> find_similar(const std::vector<std::string> &items) {
    for (unsigned i = 0; i < items.size() - 1; ++i) {
        for (unsigned j = i + 1; j < items.size(); ++j) {
            if (differ_by_one(items[i], items[j])) {
                return {i, j};               
            }
        }
    }
    return {-1, -1};
}

int main() {
    std::ifstream ifs("../data/d2input");
    if (!ifs) {
        std::cerr << "Unable to open input file." << std::endl;
        return -1;
    }
    std::string curr_item;
    std::vector<std::string> items;
    while (std::getline(ifs, curr_item)) {
        items.push_back(curr_item);
    }

    auto similar_pair = find_similar(items);
    std::string s1 = items[similar_pair.first], s2 = items[similar_pair.second];
    auto mismatch_iterator_pair = std::mismatch(s1.begin(), s1.end(), s2.begin()); 
    // debug message
    std::cout << "First item: " + s1 << std::endl;
    std::cout << "Second item: " + s2 << std::endl;
    s1.erase(mismatch_iterator_pair.first);
    std::cout << s1 << std::endl;
    return 0;
}
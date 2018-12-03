#include <iostream>
#include <fstream>
#include <vector>
#include <string>

bool have_seen(const std::vector<long long> &frequencies, long long curr_frequency) {
    for (unsigned i = 0; i < frequencies.size(); ++i) {
        if (frequencies[i] == curr_frequency) {
            return true;
        }
    }
    return false;
}

int main() {
    std::ifstream ifs("../data/d1input");
    if (!ifs) {
        std::cerr << "Unable to open input file" << std::endl;
        return -1;
    }
    std::vector<long long> input_numbers;
    std::string curr_num;
    while (std::getline(ifs, curr_num)) {
        input_numbers.push_back(std::stoll(curr_num));
    }

    long long curr_frequency = 0;
    // keep track of all frequencies that we have seen
    std::vector<long long> frequencies;
    unsigned i = 0;
    while (!have_seen(frequencies, curr_frequency)) {
        frequencies.push_back(curr_frequency);
        curr_frequency += input_numbers[i];
        i = i == input_numbers.size() - 1 ? 0 : i + 1;
    }
    std::cout << curr_frequency << std::endl;
    return 0;
}


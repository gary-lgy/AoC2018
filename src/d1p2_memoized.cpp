#include <iostream>
#include <fstream>
#include <vector>
#include <string>

int main()
{
    std::ifstream ifs("../data/d1input");
    if (!ifs)
    {
        std::cerr << "Unable to open input file" << std::endl;
        return -1;
    }
    std::vector<long long> input_numbers;
    std::string curr_num;
    while (std::getline(ifs, curr_num))
    {
        input_numbers.push_back(std::stoll(curr_num));
    }

    long long curr_frequency = 0;
    // if a particular positive frequency f has appeared previously, then positive_frequencies[f] would be true.
    // Otherwise it will be false
    // similar for negative frequencies
    // assuming frequency range possible is +-100000, initialize all 200000 entries to false
    std::vector<bool> positive_frequencies(1000000, false);
    std::vector<bool> negative_frequencies(1000000, false);
    unsigned i = 0;
    while (!(curr_frequency >= 0 ? positive_frequencies[curr_frequency] : negative_frequencies[-curr_frequency]))
    {
        if (curr_frequency >= 0)
            positive_frequencies[curr_frequency] = true;
        else
            negative_frequencies[-curr_frequency] = true;
        curr_frequency += input_numbers[i];
        i = i == input_numbers.size() - 1 ? 0 : i + 1;
    }
    std::cout << curr_frequency << std::endl;
    return 0;
}

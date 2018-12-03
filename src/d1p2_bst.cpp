#include <iostream>
#include <fstream>
#include <set>
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
    std::set<long long> frequencies;
    auto beg = input_numbers.cbegin();
    while (frequencies.find(curr_frequency) == frequencies.end())
    {
        frequencies.insert(curr_frequency);
        curr_frequency += *beg;
        ++beg;
        if (beg == input_numbers.cend())
        {
            beg = input_numbers.cbegin();
        }
    }
    std::cout << curr_frequency << std::endl;
    return 0;
}
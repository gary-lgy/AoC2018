#include <iostream>
#include <fstream>
#include <string>

int main() {
    std::ifstream ifs("../data/d1input");
    if (!ifs) {
        std::cerr << "Unable to open input file." << std::endl;
        return -1;
    }
    long long result = 0;
    std::string curr_num;
    while (std::getline(ifs, curr_num)){
        result += std::stoll(curr_num);
    }
    std::cout << result << std::endl;
    return 0;
}
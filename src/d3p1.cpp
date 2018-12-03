#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
#include <algorithm>
#include <numeric>

int main() {
    std::ifstream ifs("../data/d3input");
    if (!ifs) {
        std::cerr << "Unable to open input file" << std::endl;
        return -1;
    }

    std::vector<std::vector<unsigned>> fabric(1000, std::vector<unsigned>(1000, 0));
    std::string line;
    while (std::getline(ifs, line)) {
        std::transform(line.begin(), line.end(), line.begin(), [](char c) { return ispunct(c) || c == 'x' ? ' ' : c; });
        unsigned left_dist, top_dist, width, height;
        std::stringstream line_str(line);
        line_str >> left_dist >> left_dist >> top_dist >> width >> height;
        for (unsigned i = left_dist; i < left_dist + width; ++i) {
            for (unsigned j = top_dist; j < top_dist + height; ++j) {
                ++fabric[i][j];
            }
        }
    }
    unsigned result = std::accumulate(fabric.begin(), fabric.end(), 0, [](unsigned acc, const std::vector<unsigned> &row) {
        return std::count_if(row.begin(), row.end(), [](unsigned c) { return c >= 2; }) + acc; });
    std::cout << result << std::endl;
    return 0;
}
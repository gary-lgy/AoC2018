#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
#include <algorithm>

int main() {
    std::ifstream ifs("../data/d3input");
    if (!ifs) {
        std::cerr << "Unable to open input file" << std::endl;
        return -1;
    }

    std::vector<std::vector<std::vector<unsigned>>> fabric(1000, std::vector<std::vector<unsigned>>(1000));
    std::vector<bool> overlapped(1247, false); // 1247 is the input size
    std::string line;
    while (std::getline(ifs, line)) {
        std::transform(line.begin(), line.end(), line.begin(), [](char c) { return ispunct(c) || c == 'x' ? ' ' : c; });
        unsigned id, left_dist, top_dist, width, height;
        std::stringstream line_str(line);
        line_str >> id >> left_dist >> top_dist >> width >> height;
        for (unsigned i = left_dist; i < left_dist + width; ++i) {
            for (unsigned j = top_dist; j < top_dist + height; ++j) {
                if (fabric[i][j].empty()) {
                    fabric[i][j].push_back(id);
                } else {
                    fabric[i][j].push_back(id);
                    for (unsigned k = 0; k < fabric[i][j].size(); ++k) {
                        overlapped[fabric[i][j][k] - 1] = true;
                    }
                }
            }
        }
    }
    auto unoverlapped_iter = std::find(overlapped.begin(), overlapped.end(), false);
    std::cout << unoverlapped_iter - overlapped.begin() + 1 << std::endl;
    return 0;
}
/*************** either the problem or the solution is bugged *******************/
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <cstdlib>
#include <limits>
#include <algorithm>
#include <utility>
#include <algorithm>

int manhattan_distance(const std::pair<int, int> &point_1, const std::pair<int, int> &point_2) {
    return std::abs(point_1.first - point_2.first) + std::abs(point_1.second - point_2.second);
}

int main() {
    std::ifstream ifs("../data/d6input");
    if (!ifs) {
        std::cerr << "Unable to open input file" << std::endl;
        return -1;
    }

    std::vector<std::pair<int, int>> origins; // id -> coordinates
    std::string line;
    int x_max = std::numeric_limits<int>::min(),
        x_min = std::numeric_limits<int>::max(),
        y_max = std::numeric_limits<int>::min(),
        y_min = std::numeric_limits<int>::max();
    while (std::getline(ifs, line)) {
        line.erase(std::remove(line.begin(), line.end(), ','), line.end());
        std::stringstream line_str(line);
        int x, y;
        line_str >> x >> y;
        if (x < x_min) {
            x_min = x;
        }
        if (x > x_max) {
            x_max = x;
        }
        if (y < y_min) {
            y_min = y;
        }
        if (y > y_max) {
            y_max = y;
        }
        origins.push_back({x, y});
    }

    std::vector<int> area(origins.size(), 0); // id of origin -> area
    for (int x = x_min; x <= x_max; ++x) {
        for (int y = y_min; y <= y_max; ++y) {
            int shortest_distance = std::numeric_limits<int>::max();
            int closest_origin;
            for (int i = 0; i < origins.size(); ++i) {
                int new_distance = manhattan_distance({x, y}, origins[i]);
                if (new_distance < shortest_distance) {
                    shortest_distance = new_distance;
                    closest_origin = i;
                } else if (new_distance == shortest_distance) {
                    closest_origin = -1;
                }
            }

            if (closest_origin != -1) {
                if (x == x_min || x == x_max || y == y_min || y == y_max) {
                    area[closest_origin] = -1;
                } else {
                    ++area[closest_origin];
                }
            }
        }
    }

    // original answer output
    // int largest_area = *std::max_element(area.begin(), area.end());
    // std::cout << largest_area << std::endl;

    // debug
    std::vector<std::pair<int, int>> ans;
    for (int i = 0; i < area.size(); ++i) {
        ans.push_back({area[i], i});
    }
    std::sort(ans.begin(), ans.end());
    for (auto cur : ans) {
        std::cout << cur.first << " " << cur.second << std::endl;
    }
    
    // this solution gives the correct area map for the sample input, but does not work for the actual input
    // the correct answer is the SECOND largest area given by this solution. Why?
    return 0;
}
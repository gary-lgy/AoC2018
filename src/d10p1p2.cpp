#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <utility>
#include <algorithm>
#include <map>

const int TRY_LIMIT = 20000;

int main() {
    std::ifstream ifs("../data/d10input");
    if (!ifs) {
        std::cerr << "Unable to open file" << std::endl;
        return -1;
    }

    std::vector<std::pair<long long, long long>> pos, vel;
    std::string line;
    while (std::getline(ifs, line)) {
        std::transform(line.begin(), line.end(), line.begin(), [] (const char &c) { return isdigit(c) || c == '-' ? c : ' '; });
        std::stringstream line_str(line);
        long long x, y, dx, dy;
        line_str >> x >> y >> dx >> dy;
        pos.push_back({x, y});
        vel.push_back({dx, dy});
    }

    long long min_area = 1e18;
    int min_area_idx = -1;
    long long min_area_x_start, min_area_x_end, min_area_y_start, min_area_y_end;
    for (int i = 0; i < TRY_LIMIT; ++i) {
        long long min_x = 1e18, max_x = -1e18, min_y = 1e18, max_y = -1e18;
        for (int j = 0; j < pos.size(); ++j) {
            long long x = pos[j].first + vel[j].first * i, y = pos[j].second + vel[j].second * i;
            if (x < min_x) {
                min_x = x;
            }
            if (x > max_x) {
                max_x = x;
            }
            if (y < min_y) {
                min_y = y;
            }
            if (y > max_y) {
                max_y = y;
            }
        }
        long long area = (max_x - min_x) * (max_y - min_y);
        if (area < min_area) {
            min_area = area;
            min_area_idx = i;
            min_area_x_start = min_x;
            min_area_x_end = max_x;
            min_area_y_start = min_y;
            min_area_y_end = max_y;
        }
    }

    std::map<std::pair<long long, long long>, char> message;
    for (long y = min_area_y_start; y <= min_area_y_end; ++y) {
        for (long x = min_area_x_start; x <= min_area_x_end; ++x) {
            message[{x, y}] = ' ';
        }
    }
    for (int i = 0; i < pos.size(); ++i) {
        message[{ pos[i].first + vel[i].first * min_area_idx,
                  pos[i].second + vel[i].second * min_area_idx }] = '#';
    }

    // part 1
    for (long y = min_area_y_start; y <= min_area_y_end; ++y) {
        for (long x = min_area_x_start; x <= min_area_x_end; ++x) {
            std::cout << message[{x, y}];
        }
        std::cout << std::endl;
    }
    // part 2
    std::cout << "Waiting time: " << min_area_idx << std::endl;
    return 0;
}
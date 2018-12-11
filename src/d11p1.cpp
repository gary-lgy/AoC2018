#include <iostream>
#include <fstream>
#include <array>

int main() {
    std::ifstream ifs("../data/d11input");
    if (!ifs) {
        std::cerr << "Unable to open input file" << std::endl;
        return -1;
    }

    int grid_serial_number;
    ifs >> grid_serial_number;

    std::array<std::array<int, 300>, 300> grid;
    for (int x = 1; x <= 300; ++x) {
        for (int y = 1; y <= 300; ++y) {
            int rack_id = x + 10;
            long long power = rack_id * y;
            power += grid_serial_number;
            power *= rack_id;
            power = power / 100 % 10;
            power -= 5;
            grid[x - 1][y - 1] = power;
        }
    }

    int max_total_power = -1, top_left_x, top_left_y;
    for (int x = 1; x <= 298; ++x) {
        for (int y = 1; y <= 298; ++y) {
            int total_power = 0;
            for (int dx = 0; dx < 3; ++dx) {
                for (int dy = 0; dy < 3; ++dy) {
                    total_power += grid[x + dx - 1][y + dy - 1];
                }
            }
            if (total_power > max_total_power) {
                max_total_power = total_power;
                top_left_x = x;
                top_left_y = y;
            }
        }
    }

    std::cout << top_left_x << "," << top_left_y << std::endl;
    return 0;
}
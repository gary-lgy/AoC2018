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

    int max_total_power = -1, top_left_x, top_left_y, square_size;
    std::array<std::array<int, 300>, 300> total_power_memo = grid;
    // assuming the square with the largest total power is not 1x1
    for (int s = 2; s <= 300; ++s) {
        /* debug */ std::cout << "Square size: " << s << "x" << s << std::endl;
        for (int x = 1; x <= 301 - s; ++x) {
            for (int y = 1; y <= 301 - s; ++y) {
                int total_power = total_power_memo[x - 1][y - 1];
                for (int i = x; i < x + s - 1; ++i) {
                    total_power += grid[i - 1][y + s - 2];
                }
                for (int i = y; i < y + s; ++i) {
                    total_power += grid[x + s - 2][i - 1];
                }
                total_power_memo[x - 1][y - 1] = total_power;
                if (total_power > max_total_power) {
                    max_total_power = total_power;
                    top_left_x = x;
                    top_left_y = y;
                    square_size = s;
                }
            }
        }
    }

    std::cout << top_left_x << "," << top_left_y << "," << square_size << std::endl;
    return 0;
}
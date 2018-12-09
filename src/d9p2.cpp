#include <iostream>
#include <fstream>
#include <string>
#include <list>
#include <vector>
#include <algorithm>

std::list<long long>::iterator clockwise_next(std::list<long long> &marbles, std::list<long long>::iterator current) {
    ++current;
    if (current == marbles.end()) {
        return marbles.begin();
    } else {
        return current;
    }
}

std::list<long long>::iterator counter_clockwise_next(std::list<long long> &marbles, std::list<long long>::iterator current) {
    if (current == marbles.begin()) {
        return --marbles.end();
    } else {
        return --current;
    }
}

std::list<long long>::iterator clockwise_n(std::list<long long> &marbles, std::list<long long>::iterator current, int n) {
    for (int i = 0; i < n; ++i) {
        current = clockwise_next(marbles, current);
    }
    return current;
}

std::list<long long>::iterator counter_clockwise_n(std::list<long long> &marbles, std::list<long long>::iterator current, int n) {
    for (int i = 0; i < n; ++i) {
        current = counter_clockwise_next(marbles, current);
    }
    return current;
}

int next_player(int current, int player_count) {
    return ++current > player_count ? 1 : current;
}

int main() {
    std::ifstream ifs("../data/d9input");
    if (!ifs) {
        std::cerr << "Unable to open input file" << std::endl;
        return -1;
    }

    std::string word;
    ifs >> word;
    int player_count = std::stod(word);
    long long highest_marble;
    while (ifs >> word) {
        if (isdigit(word[0])) {
            highest_marble = std::stoll(word) * 100;
            break;
        }
    }

    std::list<long long> marbles = { 0 };
    std::list<long long>::iterator current_marble = marbles.begin();
    int current_player = 1;
    std::vector<long long> scores(player_count, 0);
    for (long long i = 1; i <= highest_marble; ++i) {
        if (i % 23 == 0) {
            scores[current_player - 1] += i;
            auto ccw_7 = counter_clockwise_n(marbles, current_marble, 7);
            scores[current_player - 1] += *ccw_7;
            current_marble = marbles.erase(ccw_7);
        } else {
            current_marble = marbles.insert(clockwise_n(marbles, current_marble, 2), i);
        }
        current_player = next_player(current_player, player_count);
    }

    long long answer = *std::max_element(scores.begin(), scores.end());
    std::cout << answer << std::endl;
    return 0;
}
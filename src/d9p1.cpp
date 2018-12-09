#include <iostream>
#include <fstream>
#include <string>
#include <list>
#include <vector>
#include <algorithm>

std::list<int>::iterator clockwise_next(std::list<int> &marbles, std::list<int>::iterator current) {
    ++current;
    if (current == marbles.end()) {
        return marbles.begin();
    } else {
        return current;
    }
}

std::list<int>::iterator counter_clockwise_next(std::list<int> &marbles, std::list<int>::iterator current) {
    if (current == marbles.begin()) {
        return --marbles.end();
    } else {
        return --current;
    }
}

std::list<int>::iterator clockwise_n(std::list<int> &marbles, std::list<int>::iterator current, int n) {
    for (int i = 0; i < n; ++i) {
        current = clockwise_next(marbles, current);
    }
    return current;
}

std::list<int>::iterator counter_clockwise_n(std::list<int> &marbles, std::list<int>::iterator current, int n) {
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
    int player_count = std::stod(word), highest_marble;
    while (ifs >> word) {
        if (isdigit(word[0])) {
            highest_marble = std::stod(word);
            break;
        }
    }

    std::list<int> marbles = { 0 };
    std::list<int>::iterator current_marble = marbles.begin();
    int current_player = 1;
    std::vector<int> scores(player_count, 0);
    for (int i = 1; i <= highest_marble; ++i) {
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

    int answer = *std::max_element(scores.begin(), scores.end());
    std::cout << answer << std::endl;
    return 0;
}
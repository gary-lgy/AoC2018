#include <iostream>
#include <fstream>
#include <forward_list>
#include <vector>

int value_of_node(std::forward_list<int> &numbers) {
    int num_of_children = numbers.front();
    numbers.pop_front();
    int num_of_metadata = numbers.front();
    numbers.pop_front();
    int value = 0;
    if (num_of_children == 0) {
        for (int i = 0; i < num_of_metadata; ++i) {
            value += numbers.front();
            numbers.pop_front();
        }
    } else {
        std::vector<int> children_values;
        for (int i = 0; i < num_of_children; ++i) {
            children_values.push_back(value_of_node(numbers));
        }
        for (int i = 0; i < num_of_metadata; ++i) {
            if (numbers.front() <= num_of_children && numbers.front() != 0) {
                value += children_values[numbers.front() - 1];
            }
            numbers.pop_front();
        }
    }
    return value;
}

int main() {
    std::ifstream ifs("../data/d8input");
    if (!ifs) {
        std::cerr << "Unable to open input file" << std::endl;
    }

    std::forward_list<int> numbers;
    int buffer;
    while (ifs >> buffer) {
        numbers.push_front(buffer);
    }
    numbers.reverse();
    
    int result = value_of_node(numbers);
    std::cout << result << std::endl;
    return 0;
}
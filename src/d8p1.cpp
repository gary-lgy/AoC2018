#include <iostream>
#include <fstream>
#include <forward_list>

int sum_of_metadata(std::forward_list<int> &numbers) {
    int num_of_children = numbers.front();
    numbers.pop_front();
    int num_of_metadata = numbers.front();
    numbers.pop_front();
    int metadata = 0;
    for (int i = 0; i < num_of_children; ++i) {
        metadata += sum_of_metadata(numbers);
    }
    for (int i = 0; i < num_of_metadata; ++i) {
        metadata += numbers.front();
        numbers.pop_front();
    }
    return metadata;
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
    
    int result = sum_of_metadata(numbers);
    std::cout << result << std::endl;
    return 0;
}
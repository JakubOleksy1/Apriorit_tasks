#include "LinkedList.hpp"

int main() {
    LinkedList<int> list = {1, 42, 3, 56, 78, 99, 23, 45, 67, 89, 100, 34, 12, 76, 54};
    auto tail = list.split_when([](const int& value) { return value == 99; });

    std::cout << "Original list: ";
    for (const auto& value : list) {
        std::cout << value << " ";
    }
    std::cout << "\n";

    std::cout << "Tail list: ";
    for (const auto& value : tail) {
        std::cout << value << " ";
    }
    std::cout << "\n";

    return 0;
}
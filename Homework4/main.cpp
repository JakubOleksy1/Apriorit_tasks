#include <iostream>
#include "MyVectorFixed.hpp"

int main()
{
    MyVectorFixed<int> vec;
    vec.push_back(1, "one");
    vec.push_back(2, "two");

    std::cout << "Element at index 0: " << vec[0].first << ", " << vec[0].second << std::endl;
    std::cout << "Element with name 'two': " << vec["two"] << std::endl;

    return 0;
}
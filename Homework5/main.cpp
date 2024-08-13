#include "CustomSmartPointers.hpp"

int main() {
    SharedPtr<int> shared(new int(24));
    WeakPtr<int> weak = shared;

    std::cout << "Shared use count: " << shared.UseCount() << std::endl;
    std::cout << "Weak use count: " << weak.UseCount() << std::endl;

    return 0;
}
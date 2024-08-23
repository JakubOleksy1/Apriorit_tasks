#include <QCoreApplication>
#include <iostream>
#include "counter.h"

void printValues(const Counter &c1, const Counter &c2) {
    std::cout << "Counter 1 Value: " << c1.value() << std::endl;
    std::cout << "Counter 2 Value: " << c2.value() << std::endl;
}

int main(int argc, char *argv[]) {
    QCoreApplication a(argc, argv);

    Counter counter1(5);
    Counter counter2(50);

    QObject::connect(&counter1, &Counter::valueChanged, &counter2, &Counter::setValue);
    QObject::connect(&counter2, &Counter::valueChanged, &counter1, &Counter::setValue);

    std::cout << "Initial values:" << std::endl;
    printValues(counter1, counter2);

    std::cout << "\nIncrement Counter 1:" << std::endl;
    counter1.increment();
    printValues(counter1, counter2);

    std::cout << "\nIncrement Counter 2:" << std::endl;
    counter2.increment();
    printValues(counter1, counter2);

    std::cout << "\nDecrement Counter 1:" << std::endl;
    counter1.decrement();
    printValues(counter1, counter2);

    std::cout << "\nDecrement Counter 2:" << std::endl;
    counter2.decrement();
    printValues(counter1, counter2);

    return a.exec();
}

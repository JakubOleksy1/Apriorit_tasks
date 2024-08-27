#include "functions.h"

int GetProductsAmount(const std::vector<int>& prices, int budget) {
    int count = 0;
    for (int price : prices) {
        if (price <= budget) {
            count++;
            budget -= price;
        }
    }
    return count;
}

bool IsLeapYear(int year) {
    if (year % 4 != 0) {
        return false;
    } else if (year % 100 != 0) {
        return true;
    } else if (year % 400 != 0) {
        return false;
    } else {
        return true;
    }
}


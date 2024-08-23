#include <vector>
#include <algorithm>

int GetProductsAmount(std::vector<int> prices, int amountOfMoney) {
    std::sort(prices.begin(), prices.end());

    int sum = 0;
    for (size_t i = 0; i < prices.size(); ++i) {
        sum += prices[i];
        if (sum > amountOfMoney) {
            return i;
        }
    }

    return prices.size();
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
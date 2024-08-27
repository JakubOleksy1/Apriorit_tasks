#include "functions.h"
#include <gtest/gtest.h>

// Test cases for GetProductsAmount
TEST(GetProductsAmountTest, NoProducts) {
    std::vector<int> prices = {};
    EXPECT_EQ(GetProductsAmount(prices, 100), 0);
}

TEST(GetProductsAmountTest, SingleProductAffordable) {
    std::vector<int> prices = {50};
    EXPECT_EQ(GetProductsAmount(prices, 100), 1);
}

TEST(GetProductsAmountTest, SingleProductNotAffordable) {
    std::vector<int> prices = {150};
    EXPECT_EQ(GetProductsAmount(prices, 100), 0);
}

TEST(GetProductsAmountTest, MultipleProductsSomeAffordable) {
    std::vector<int> prices = {50, 30, 20, 10};
    EXPECT_EQ(GetProductsAmount(prices, 60), 2); }

// Test cases for IsLeapYear
TEST(IsLeapYearTest, CommonYear) {
    EXPECT_FALSE(IsLeapYear(2019));
}

TEST(IsLeapYearTest, LeapYear) {
    EXPECT_TRUE(IsLeapYear(2020));
}

TEST(IsLeapYearTest, CenturyYearNotLeap) {
    EXPECT_FALSE(IsLeapYear(1900));
}

TEST(IsLeapYearTest, CenturyYearLeap) {
    EXPECT_TRUE(IsLeapYear(2000));
}

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
#include <gtest/gtest.h>
#include "main.cpp"

//Products Amount
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
    EXPECT_EQ(GetProductsAmount(prices, 60), 2);
}

TEST(GetProductsAmountTest, MultipleProductsAllAffordable) {
    std::vector<int> prices = {10, 20, 30, 40};
    EXPECT_EQ(GetProductsAmount(prices, 100), 4);
}

TEST(GetProductsAmountTest, MultipleProductsNoneAffordable) {
    std::vector<int> prices = {100, 200, 300};
    EXPECT_EQ(GetProductsAmount(prices, 50), 0);
}

//Lap year
TEST(IsLeapYearTest, CommonYearNotDivisibleBy4) {
    EXPECT_FALSE(IsLeapYear(1997));
}

TEST(IsLeapYearTest, LeapYearDivisibleBy4) {
    EXPECT_TRUE(IsLeapYear(1996));
}

TEST(IsLeapYearTest, CommonYearDivisibleBy100) {
    EXPECT_FALSE(IsLeapYear(1900));
}

TEST(IsLeapYearTest, LeapYearDivisibleBy400) {
    EXPECT_TRUE(IsLeapYear(2000));
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
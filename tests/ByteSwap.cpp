//
// Created by qazer on 09.04.2019.
//

#include <gtest/gtest.h>
#include "utils/ByteSwap.h"

TEST(ByteSwap, 2Bytes)
{
    uint16_t num = 24567;
    uint16_t result = ByteSwapImpl<uint16_t >().exec(ByteSwapImpl<uint16_t>().exec(num));
    EXPECT_EQ(num, result);
}

TEST(ByteSwap, 4Bytes)
{
    uint16_t num = 24567;
    uint16_t result = ByteSwapImpl<uint32_t >().exec(ByteSwapImpl<uint32_t>().exec(num));
    EXPECT_EQ(num, result);
}

TEST(ByteSwap, 8Bytes)
{
uint64_t num = 24567;
uint64_t result = ByteSwapImpl<uint64_t >().exec(ByteSwapImpl<uint64_t>().exec(num));
EXPECT_EQ(num, result);
}

TEST(ByteSwap, TemplateUnion)
{
    uint32_t input = 123;
    TemplateUnion<uint32_t, float> x(input);
    TemplateUnion<float, uint32_t> y(x.get());
    uint32_t output = y.get();
    EXPECT_EQ(input, output);
}

TEST(TemplateSwapper, float)
{
    float floatNum = 5.0;
    float swappedFloat = ByteSwapper<float>().get(floatNum);
    float doubleSwappedFloat = ByteSwapper<float>().get(swappedFloat);
    EXPECT_LE(std::abs(floatNum-doubleSwappedFloat), 0.1);
}

TEST(TemplateSwapper, double)
{
    double doubleNum = 5.0;
    double swappedDouble = ByteSwapper<double>().get(doubleNum);
    double doubleSwappedDouble = ByteSwapper<double>().get(swappedDouble);
    EXPECT_LE(std::abs(doubleNum-doubleSwappedDouble), 0.1);
}


TEST(TemplateSwapper, char)
{
    char character = 'd';
    char swappedCharacter = ByteSwapper<char>().get(character);
    char doubleSwappedCharacter = ByteSwapper<char>().get(swappedCharacter);
    EXPECT_EQ(character, swappedCharacter);
    EXPECT_EQ(swappedCharacter, doubleSwappedCharacter);
}

TEST(TemplateSwapper, bool)
{
    bool bl = false;
    bool swappedbool = ByteSwapper<bool>().get(bl);
    char doubleSwappedBl = ByteSwapper<char>().get(swappedbool);
    EXPECT_EQ(doubleSwappedBl, swappedbool);
    EXPECT_EQ(swappedbool, doubleSwappedBl);
}
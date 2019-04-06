//
// Created by qazer on 06.04.2019.
//
#include <gtest/gtest.h>
#include "../src/include/BitStream.h"

TEST(BitStream, uint16_t)
{
    BitStream bitStream(256);
    uint16_t data = 2000;
    uint16_t newData = 0;
    bitStream.Write<uint16_t>(data, 16);
    ASSERT_EQ(newData, 2000);
}

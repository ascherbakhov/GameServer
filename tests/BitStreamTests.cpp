//
// Created by qazer on 06.04.2019.
//
#include <gtest/gtest.h>
#include "../src/include/BitStream.h"

TEST(BitStream, typesSerialization)
{
    BitStream bitStream(256);
    uint16_t int16 = 2000;
    uint16_t newInt16;

    uint8_t int8 = 250;
    uint8_t newInt8;

    bool bl = true;
    bool newBl;

    bitStream.Write(int16);
    bitStream.Write(int8);
    bitStream.Write(bl);

    BitStream bitStream2(bitStream);
    bitStream2.Read(newInt16);
    bitStream2.Read(newInt8);
    bitStream.Read(newBl);
    EXPECT_EQ(newInt16, int16);
    EXPECT_EQ(newInt8, int8);
    EXPECT_EQ(newBl, bl);
}

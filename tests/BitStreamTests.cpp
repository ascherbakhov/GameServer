//
// Created by qazer on 06.04.2019.
//
#include <gtest/gtest.h>
#include "../src/include/BitStream.h"

TEST(BitStream, typesSerialization)
{
    OutputBitStream bitStream(256);
    uint16_t int16 = 2000;
    uint16_t newInt16;

    uint8_t int8 = 250;
    uint8_t newInt8;

    bool bl = true;
    bool newBl, newBl2;

    bitStream.Write(int16);
    bitStream.Write(bl);
    bitStream.Write(int8);
    bitStream.Write(bl);

    InputBitStream bitStream2(bitStream.GetBuffer(), bitStream.GetSize());
    bitStream2.Read(newInt16);
    bitStream2.Read(newBl);
    bitStream2.Read(newInt8);
    bitStream2.Read(newBl2);

    EXPECT_EQ(newInt16, int16);
    EXPECT_EQ(newInt8, int8);
    EXPECT_EQ(newBl, bl);
    EXPECT_EQ(newBl2, bl);
}

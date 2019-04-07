//
// Created by qazer on 06.04.2019.
//
#include <gtest/gtest.h>
#include "../src/include/BitStream.h"

TEST(BitStream, typesSerialization)
{
    OutputBitStream bitStream(256);
    uint16_t uint16 = 2000;
    uint16_t newInt16;

    uint8_t uint8 = 250;
    uint8_t newInt8;

    uint32_t uint32 = 99999;
    uint32_t newUint32;

    uint64_t uint64 = 99999999;
    uint64_t newUint64;

    float floatNum = 1233.1;
    float floatNew;

    double doubleNum = 12312.123;
    double doubleNew = 12321.312;


    std::string str("LevelUp");
    std::string newStr;

    bitStream.Write(uint32);
    bitStream.Write(uint8);
    bitStream.Write(str);
    bitStream.Write(uint16);
    bitStream.Write(floatNum);
    bitStream.Write(doubleNum);
    bitStream.Write(uint64);


    InputBitStream bitStream2(bitStream.GetBuffer(), bitStream.GetSize());
    bitStream2.Read(newUint32);
    bitStream2.Read(newInt8);
    bitStream2.Read(newStr);
    bitStream2.Read(newInt16);
    bitStream2.Read(floatNew);
    bitStream2.Read(doubleNew);
    bitStream2.Read(newUint64);



    EXPECT_EQ(newInt16, uint16);
    EXPECT_EQ(newInt8, uint8);
    EXPECT_EQ(newUint32, uint32);
    EXPECT_EQ(newUint64, uint64);
    EXPECT_EQ(floatNum, floatNew);
    EXPECT_EQ(doubleNum, doubleNew);
    EXPECT_EQ(newStr, str);
}

TEST(BitStream, BoolTest)
{
    typedef uint8_t addType;
    addType num = 234;
    addType newNum;

    bool bl = true;
    bool newBl;

    OutputBitStream bitStream(256);
    bitStream.Write(bl);
    bitStream.Write(num);

    InputBitStream bitStream2(bitStream.GetBuffer(), bitStream.GetSize());
    bitStream2.Read(newBl);
    bitStream2.Read(newNum);

    EXPECT_EQ(bl, newBl);
    EXPECT_EQ(num, newNum);
}

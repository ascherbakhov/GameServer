//
// Created by qazer on 04.04.2019.
//

#include <cstring>
#include <algorithm>
#include "BitStream.h"

void BitStream::Read(void *data, size_t size) {

}

void BitStream::Write(uint8_t data, size_t size) {
    bufflen_t newHead = mHead + static_cast<bufflen_t>(size);
    if (newHead > mHead)
    {
        Reallocate(std::max<bufflen_t>(2 * mCapacity, newHead));
    }
    bufflen_t lastByte = mHead >> 3;
    bufflen_t lastBit = mHead & 0x7;
    bufflen_t bitsFree = 8 - lastBit;
    uint8_t  mask = ~(0xff << lastBit);
    if (bitsFree < size)
    {
        mBuffer[lastByte + 1] = data >> bitsFree;
    }
    mHead = newHead;
}

void BitStream::Reallocate(bufflen_t newBitSize) {
    if (mBuffer == nullptr)
    {
        mCapacity = newBitSize;
        mBuffer = static_cast<char *>(std::malloc(newBitSize >> 3));
        memset(mBuffer, 0, newBitSize >> 3);
    }
    else
    {
        char* newBuffer =  static_cast<char *>(std::malloc(newBitSize >> 3));
        memset(mBuffer, 0, newBitSize >> 3);
        memcpy(newBuffer, mBuffer, newBitSize >> 3);
        std::free(mBuffer);
        mBuffer = newBuffer;
    }

}

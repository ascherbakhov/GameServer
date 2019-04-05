//
// Created by qazer on 04.04.2019.
//

#include <cstring>
#include <algorithm>
#include "BitStream.h"

void BitStream::Read(void *data, size_t size) {

}

void BitStream::WriteBits(uint8_t data, size_t size)
{
    bufflen_t newHead = mHead + static_cast<bufflen_t>(size);
    if (newHead > mHead)
    {
        Reserve(std::max<bufflen_t>(2 * mCapacity, newHead));
    }
    bufflen_t byteHead = mHead >> 3;
    bufflen_t bitHead = mHead & 0x7;
    bufflen_t bitsFree = 8 - bitHead;

    //We want to write out 10111111 to [1 byte][0 byte]: [XXXXXXX][XXX10101]
    //Result should be [XXX10111][11110101].
    //data << bitHead would be 11100000
    //data >> bitsFree would be 00010111
    mBuffer[byteHead] |= (data << bitHead);

    if (bitsFree < size)
    {
        mBuffer[byteHead + 1] = data >> bitsFree;
    }
    mHead = newHead;
}

void BitStream::WriteBits(const void* data, size_t size)
{
    const char* src = static_cast<const char*>(data);
    while(size > 0)
    {
        size_t bitsToWrite = std::min<size_t>(8, size);
        WriteBits(*src, bitsToWrite);
        size -= bitsToWrite;
        ++src;
    }
}


void BitStream::Reserve(bufflen_t newBitSize)
{
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

void BitStream::Write(bool data, size_t size)
{
    WriteBits(&data, size);
}

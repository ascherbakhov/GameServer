//
// Created by qazer on 10.04.2019.
//

#include <utils/ByteSwap.h>
#include "DataStructures/OutputBitStream.h"


OutputBitStream::OutputBitStream(bufflen_t capacity) : mBuffer(nullptr), mHead(0), mCapacity(0), isLittleEndian(IsLittleEndian())
{
    Reserve(capacity);
}

OutputBitStream::OutputBitStream(const OutputBitStream &other): mCapacity(other.mCapacity), mHead(other.mHead), isLittleEndian(other.isLittleEndian)
{
    int byteCount = mCapacity >> BYTE_SHIFT;
    mBuffer = static_cast<byte*>(malloc(byteCount));
    memcpy(mBuffer, other.mBuffer, byteCount);
}


void OutputBitStream::WriteBits(byte data, bufflen_t size)
{
    bufflen_t newHead = mHead + size;
    if (newHead > mCapacity)
    {
        Reserve(std::max<bufflen_t>(2 * mCapacity, newHead));
    }
    bufflen_t byteHead = mHead >> BYTE_SHIFT;
    bufflen_t bitHead = mHead & 0x7;
    bufflen_t bitsFree = BITS_PER_BYTE - bitHead;

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

void OutputBitStream::WriteBits(const void* data, bufflen_t size)
{
    const byte* src = static_cast<const byte*>(data);
    while(size > 0)
    {
        size_t bitsToWrite = std::min<size_t>(BITS_PER_BYTE, size);
        WriteBits(*src, bitsToWrite);
        size -= bitsToWrite;
        ++src;
    }
}

void OutputBitStream::Reserve(bufflen_t newBitSize)
{
    if (mBuffer == nullptr)
    {
        mCapacity = newBitSize;
        mBuffer = static_cast<byte *>(std::malloc(newBitSize >> BYTE_SHIFT));
        memset(mBuffer, '\0', newBitSize >> BYTE_SHIFT);
    }
    else
    {
        byte* newBuffer =  static_cast<byte *>(std::malloc(newBitSize >> BYTE_SHIFT));
        memset(newBuffer, '\0', newBitSize >> BYTE_SHIFT);
        memcpy(newBuffer, mBuffer, newBitSize >> BYTE_SHIFT);
        std::free(mBuffer);
        mBuffer = newBuffer;
    }
}

void OutputBitStream::Write(std::string& str)
{
    auto elementsCount = static_cast<uint32_t>(str.size());
    Write(elementsCount);
    for (const auto element : str)
    {
        Write(element);
    }
}

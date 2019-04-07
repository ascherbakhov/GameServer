//
// Created by qazer on 04.04.2019.
//

#include <cstring>
#include <algorithm>
#include "include/BitStream.h"


void BitStream::WriteBits(byte data, size_t size)
{
    bufflen_t newHead = mHead + static_cast<bufflen_t>(size);
    if (newHead > mHead)
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

void BitStream::WriteBits(const void* data, size_t size)
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


void BitStream::Reserve(bufflen_t newBitSize)
{
    if (mBuffer == nullptr)
    {
        mCapacity = newBitSize;
        mBuffer = static_cast<byte *>(std::malloc(newBitSize >> BYTE_SHIFT));
        memset(mBuffer, 0, newBitSize >> BYTE_SHIFT);
    }
    else
    {
        byte* newBuffer =  static_cast<byte *>(std::malloc(newBitSize >> BYTE_SHIFT));
        memset(newBuffer, 0, newBitSize >> BYTE_SHIFT);
        memcpy(newBuffer, mBuffer, newBitSize >> BYTE_SHIFT);
        std::free(mBuffer);
        mBuffer = newBuffer;
    }

}

//TODO: check thin function
void BitStream::ReadBits(byte& data, size_t size)
{
    bufflen_t byteHead = mHead >> BYTE_SHIFT;
    bufflen_t bitHead = mHead & 0x7;
    bufflen_t bitsFree = BITS_PER_BYTE - bitHead;

    data = static_cast<byte>(mBuffer[byteHead]) >> bitHead;
    if( bitsFree < size )
    {
        data |= static_cast< byte >( mBuffer[ bitHead + 1 ] ) << bitsFree;
    }

    data &= ( ~( 0x00ff << size ) );

    mHead += size;
}

void BitStream::ReadBits(void* data, size_t size)
{
    byte* dest = reinterpret_cast<byte*>(data);
    while (size > 0)
    {
        size_t bitsToRead = std::min<size_t>(BITS_PER_BYTE, size);
        ReadBits(*dest, bitsToRead);
        size -= BITS_PER_BYTE;
        ++dest;
    }
}
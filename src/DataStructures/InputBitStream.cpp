//
// Created by qazer on 10.04.2019.
//

#include <utils/ByteSwap.h>
#include "DataStructures/InputBitStream.h"

InputBitStream::InputBitStream(const byte *buffer, bufflen_t size): mHead(0), isLittleEndian(IsLittleEndian())
{
    int byteCount = (size % BITS_PER_BYTE == 0) ? (size >> BYTE_SHIFT) : ((size >> BYTE_SHIFT) + 1);
    mBuffer = static_cast<byte*>(malloc(byteCount));
    memcpy(mBuffer, buffer, byteCount);
}

void InputBitStream::Read(std::string& inStr)
{
    uint32_t elementsCount;
    Read(elementsCount);
    inStr.resize(elementsCount);
    for (auto& element: inStr)
    {
        Read(element);
    }
}

void InputBitStream::ReadBits(byte& data, bufflen_t size)
{
    bufflen_t byteHead = mHead >> BYTE_SHIFT;
    bufflen_t bitHead = mHead & 0x7;
    bufflen_t bitsFree = BITS_PER_BYTE - bitHead;

    data = mBuffer[byteHead] >> bitHead;
    if( bitsFree < size )
    {
        data |=  mBuffer[ byteHead + 1 ]  << bitsFree;
    }

    //Just apply mask to take only bits we want(for example only 1st bit for bool)
    data &= ( ~( 0xff << size ) );

    mHead += size;
}

void InputBitStream::ReadBits(void* data, bufflen_t size)
{
    byte* dest = reinterpret_cast<byte*>(data);
    while (size > 0)
    {
        bufflen_t bitsToRead = std::min<bufflen_t>(BITS_PER_BYTE, size);
        ReadBits(*dest, bitsToRead);
        size -= bitsToRead;
        ++dest;
    }
}

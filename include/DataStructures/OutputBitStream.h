//
// Created by qazer on 10.04.2019.
//

#ifndef NETWORK_OUTPUTBITSTREAM_H
#define NETWORK_OUTPUTBITSTREAM_H

#include <string>
#include <cstring>
#include "../utils/Constants.h"
#include "../utils/ByteSwap.h"

class OutputBitStream {
private:
    bufflen_t mCapacity;
    bufflen_t mHead;
    byte* mBuffer;
    bool isLittleEndian; // Stream endianness is little endian

    void WriteBits(byte data, bufflen_t size);
    void WriteBits(const void *data, bufflen_t size);

public:
    explicit OutputBitStream(bufflen_t capacity);
    OutputBitStream(const OutputBitStream& other);
    ~OutputBitStream(){ std::free(mBuffer); }

    void Reserve(bufflen_t newBitSize);
    byte* GetBuffer() {return mBuffer;}
    bufflen_t GetSize() {return mHead;}

    template <class T>
    void Write(T data, bufflen_t size = sizeof(T) * BITS_PER_BYTE)
    {
        static_assert(std::is_arithmetic<T>::value || std::is_enum<T>::value,
                      "Generic BitStream::Write supports only arithmetic or enum types");
        if (isLittleEndian)
        {
            WriteBits(&data, size);
        }
        else
        {
            data = SwapBytes(data);
            WriteBits(&data, size);
        }
    }
    void Write(bool data) { WriteBits(data, 1); };
    void Write(std::string& str);
};

#endif //NETWORK_OUTPUTBITSTREAM_H

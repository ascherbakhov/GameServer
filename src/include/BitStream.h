//
// Created by qazer on 04.04.2019.
//

#ifndef NETWORK_BITSTREAM_H
#define NETWORK_BITSTREAM_H


#include <cstdint>
#include <cstdlib>
#include <string>

typedef uint16_t bufflen_t;
typedef char byte;

const size_t BITS_PER_BYTE = 8;
const uint8_t BYTE_SHIFT = 3;

class OutputBitStream {
private:
    bufflen_t mCapacity;
    bufflen_t mHead;
    byte* mBuffer;

    void WriteBits(byte data, size_t size);
    void WriteBits(const void *data, size_t size);

public:
    explicit OutputBitStream(bufflen_t capacity): mBuffer(nullptr), mHead(0), mCapacity(0)
    {
        Reserve(capacity);
    }
    OutputBitStream(const OutputBitStream& other): mCapacity(other.mCapacity), mHead(other.mHead)
    {
        int byteCount = mCapacity >> BYTE_SHIFT;
        mBuffer = static_cast<byte*>(malloc(byteCount));
        memcpy(mBuffer, other.mBuffer, byteCount);
    }
    ~OutputBitStream(){ std::free(mBuffer); }

    void Reserve(bufflen_t newBitSize);
    byte* GetBuffer() {return mBuffer;}
    bufflen_t GetSize() {return mHead;}

    template <class T>
    void Write(T data, size_t size = sizeof(T) * BITS_PER_BYTE)
    {
        static_assert(std::is_arithmetic<T>::value || std::is_enum<T>::value,
                      "Generic BitStream::Write supports only arithmetic or enum types");
        WriteBits(&data, size);
    }
    void Write(bool data) { WriteBits(&data, 1); };
    void Write(std::string& str);
};


class InputBitStream {
private:
    bufflen_t mHead;
    byte* mBuffer;


    void ReadBits(byte &data, size_t size);
    void ReadBits(void* data, size_t size);

public:
    explicit InputBitStream(const byte* buffer, bufflen_t size): mHead(0)
    {
        int byteCount = (size % BITS_PER_BYTE == 0) ? (size >> BYTE_SHIFT) : ((size >> BYTE_SHIFT) + 1);
        mBuffer = static_cast<byte*>(malloc(byteCount));
        memcpy(mBuffer, buffer, byteCount);
    }
    ~InputBitStream(){ std::free(mBuffer); }

    template <class T>
    void Read(T& data, size_t size = sizeof(T) * BITS_PER_BYTE)
    {
        static_assert(std::is_arithmetic<T>::value || std::is_enum<T>::value,
                      "Generic BitStream::Read supports only arithmetic or enum types");
        ReadBits(&data, size);
    };
    void Read(bool& data) { ReadBits(&data, 1); }
    void Read(std::string& inStr);
};


#endif //NETWORK_BITSTREAM_H

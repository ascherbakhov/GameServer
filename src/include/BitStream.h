//
// Created by qazer on 04.04.2019.
//

#ifndef NETWORK_BITSTREAM_H
#define NETWORK_BITSTREAM_H


#include <cstdint>
#include <cstdlib>

typedef uint16_t bufflen_t;
typedef char byte;

const size_t BITS_PER_BYTE = 8;
const uint8_t BYTE_SHIFT = 3;

class BitStream {
private:
    bufflen_t mCapacity;
    bufflen_t mHead;

    void WriteBits(byte data, size_t size);
    void WriteBits(const void *data, size_t size);

    void ReadBits(byte &data, size_t size);
    void ReadBits(void* data, size_t size);

public:
    byte* mBuffer;

    explicit BitStream(bufflen_t capacity):
    mBuffer(nullptr), mHead(0), mCapacity(0)
    {
        Reserve(capacity);
    }
    ~BitStream(){ std::free(mBuffer); }
    void Reserve(bufflen_t newBitSize);
    bufflen_t GetBufferSizeLeft(){ return mCapacity - mHead;}

    template <class T>
    void Write(T data, size_t size = sizeof(T) * BITS_PER_BYTE)
    {
        static_assert(std::is_arithmetic<T>::value || std::is_enum<T>::value,
                      "Generic BitStream::Write supports only arithmetic or enum types");
        WriteBits(&data, size);
    }
    void Write(bool data) { WriteBits(&data, 1); };

    template <class T>
    void Read(T& data, size_t size = sizeof(T) * BITS_PER_BYTE)
    {
        static_assert(std::is_arithmetic<T>::value || std::is_enum<T>::value,
                      "Generic BitStream::Read supports only arithmetic or enum types");
        ReadBits(&data, size);
    };
    void Read(bool& data) { ReadBits(&data, 1); }


};


#endif //NETWORK_BITSTREAM_H

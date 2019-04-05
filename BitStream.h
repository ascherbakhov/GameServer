//
// Created by qazer on 04.04.2019.
//

#ifndef NETWORK_BITSTREAM_H
#define NETWORK_BITSTREAM_H


#include <cstdint>
#include <cstdlib>

typedef uint16_t bufflen_t;

class BitStream {
private:
    bufflen_t mCapacity;
    bufflen_t mHead;
    char* mBuffer;

    void WriteBits(uint8_t data, size_t size);
    void WriteBits(const void *data, size_t size);

public:
    BitStream(bufflen_t capacity) { Reserve(512); }
    ~BitStream(){ std::free(mBuffer); }
    bufflen_t GetBufferSizeLeft(){ return mCapacity - mHead;}

    template <class T>
    void Write(T data, size_t size = sizeof(T) * 8)
    {
        static_assert(std::is_arithmetic<T>::value || std::is_enum<T>::value,
                      "Generic BitStream::Write supports only arithmetic or enum types");
        WriteBits(&data, size);
    }

    void Write(bool data, size_t size = 1);
    void Read(void* data, size_t size);
    void Reserve(bufflen_t newBitSize);

};


#endif //NETWORK_BITSTREAM_H

//
// Created by qazer on 04.04.2019.
//

#ifndef NETWORK_BITSTREAM_H
#define NETWORK_BITSTREAM_H


#include <cstdint>
#include <cstdlib>

typedef uint16_t bufflen_t;

class BitStream {
public:
    BitStream(bufflen_t capacity) { Reallocate(512); }
    ~BitStream(){std::free(mBuffer);}
    bufflen_t GetBufferSizeLeft(){ return mCapacity - mHead;}
    void Write(uint8_t data, size_t size);
    void Read(void* data, size_t size);
    void Reallocate(bufflen_t newBitSize);
private:
    bufflen_t mCapacity;
    bufflen_t mHead;
    char* mBuffer;
};


#endif //NETWORK_BITSTREAM_H

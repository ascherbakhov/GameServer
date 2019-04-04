//
// Created by qazer on 04.04.2019.
//

#ifndef NETWORK_ISTREAM_H
#define NETWORK_ISTREAM_H


#include <cstdint>
#include <cstdlib>

typedef uint16_t buffer_t;

class IStream {
public:
    IStream(buffer_t capacity) : mCapacity(capacity){}
    ~IStream(){std::free(mBuffer);}
    buffer_t GetBufferSizeLeft(){ return mCapacity - mHead;}
private:
    buffer_t mCapacity;
    buffer_t mHead;
    char* mBuffer;
};


#endif //NETWORK_ISTREAM_H

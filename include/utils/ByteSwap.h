//
// Created by qazer on 08.04.2019.
//

#ifndef NETWORK_BYTESWAP_H
#define NETWORK_BYTESWAP_H

#include <cstdint>
#include <cstddef>
#include <type_traits>

/*
 * WARNING: this implementation was made for fun and practicing templates.
 * But nothing is more permanent than temporary :)
 *
 * The main class is ByteSwapper. It is used to swap bytes from little to big endinan and back.
 * For example, ByteSwapper<T>().get(data), where T is actual type of "data".
 *
 * It uses swapper implementation below(ByteSwapImpl), that takes only integers, to swap bytes.
 * But sometimes we want to swap not integer types.
 *
 * To overcome this TemplateUnion(and IntAsType with TypeAsInt helpers) class is used.
 * It takes any type as a template parameter and returns integer with the same amount
 * of bytes as input type without casting.
 *
 * SameSizedInt is alias for int type of same amounts of byte as template parameter type.
 * For example SameSizedInt<double> is uint64_t
 */


//////////////////////////////////////////////////////////
//Swapper functions implementations for different bit size
//////////////////////////////////////////////////////////
template <class T> class ByteSwapImpl;

template <>
class ByteSwapImpl<uint8_t>{
public:
    inline uint8_t operator()(uint8_t data)
    {
        return data;
    };
};

template <>
class ByteSwapImpl<uint16_t>{
public:
    inline uint16_t operator()(uint16_t data)
    {
        return data << 8 | data >> 8;
    };
};

template <>
class ByteSwapImpl<uint32_t>{
public:
    inline uint32_t operator()(uint32_t data)
    {
        return
                data << 24 & 0xff000000 |
                data << 8 & 0x00ff0000 |
                data >> 8 &  0x0000ff00 |
                data >> 24 & 0x000000ff ;
    }
};

template <>
class ByteSwapImpl<uint64_t>
{
public:
    inline uint64_t operator()(uint64_t data)
    {
        return
                data << 56 & 0xff00000000000000 |
                data << 40 & 0x00ff000000000000 |
                data << 24 & 0x0000ff0000000000 |
                data << 8 &  0x000000ff00000000 |
                data >> 8 &  0x00000000ff000000 |
                data >> 24 & 0x0000000000ff0000 |
                data >> 40 & 0x000000000000ff00 |
                data >> 56 & 0x00000000000000ff ;
    }
};

//////////////////////////////////////////////////////////
//End Swapper functions
//////////////////////////////////////////////////////////

template <class fromType, class toType>
class TemplateUnion
{
public:
    explicit TemplateUnion(fromType value): input(value){}
    toType& get(){ return output;}
private:
    union {
        fromType input;
        toType output;
    };
};

template <size_t size>
using UintOfSize =
typename std::conditional<size == 1, uint8_t,
        typename std::conditional<size == 2, uint16_t,
                typename std::conditional<size == 4, uint32_t,
                uint64_t>::type
        >::type
>::type;

template <class T>
using TypeAsInt = TemplateUnion< T, UintOfSize<sizeof(T)> >;

template <class T>
using IntAsType = TemplateUnion< UintOfSize<sizeof(T)>, T >;

template <class T>
class ByteSwapper
{
public:
    T get(T value) const
    {
        using uint_t = UintOfSize<sizeof(T)>;

        auto swapFunc = ByteSwapImpl<uint_t>();
        auto intDataToSwap = TypeAsInt<T>(value).get();
        uint_t output = swapFunc(intDataToSwap);
        return IntAsType<T>(output).get();
    }
};
template <class T>
T SwapBytes(T value)
{
    return ByteSwapper<T>().get(value);
}

inline int IsBigEndian()
{
    int i=1;
    return ! *((char *)&i);
}

#endif //NETWORK_BYTESWAP_H

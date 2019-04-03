//
// Created by qazer on 04.04.2019.
//

#include <netinet/in.h>
#include <arpa/inet.h>
#include "SocketAddress.h"

SocketAddress::SocketAddress(const char* ip_addr, u_int16_t port) {
    sockaddr_in addr{}; // Maybe removed after exitiing
    addr.sin_family = AF_INET;
    inet_pton(AF_INET, ip_addr, &addr.sin_addr.s_addr);
    mAddress = reinterpret_cast<sockaddr*>(&addr);
}

sockaddr *SocketAddress::Get() {
    return mAddress;
}

size_t SocketAddress::Size()
{
    return sizeof(*mAddress);
}
//
// Created by qazer on 04.04.2019.
//

#include <netinet/in.h>
#include <arpa/inet.h>
#include <spdlog/spdlog.h>
#include "SockAddr.h"

SockAddr::SockAddr(const char* ip_addr, uint16_t port) {
    mAddress.sin_family = AF_INET;
    mAddress.sin_port = htons(port);
    inet_pton(AF_INET,  ip_addr, &(mAddress.sin_addr));
}

size_t SockAddr::Size()
{
    return sizeof(mAddress);
}

sockaddr* SockAddr::Get() {
    return reinterpret_cast<sockaddr*>(&mAddress);
}

SockAddr::SockAddr(const sockaddr_in& address) {
    memcpy(&mAddress, &address, sizeof(address));
}


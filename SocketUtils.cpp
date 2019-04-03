//
// Created by qazer on 04.04.2019.
//

#include "SocketUtils.h"

UDPSocketPtr SocketUtils::createUDPSocket() {
    int s = socket(AF_INET, SOCK_DGRAM, 0);
    if (s > 0)
    {
        return std::make_shared<UDPSocket>(new UDPSocket());
    }
    else
    {
        spdlog::error("SocketUtils::createUDPSocket");
        return nullptr;
    }
}

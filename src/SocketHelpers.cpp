//
// Created by qazer on 04.04.2019.
//

#include "include/SocketHelpers.h"

UDPSocketPtr SocketHelpers::createUDPSocket() {
    int sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    if (sockfd > 0)
    {
        return UDPSocketPtr(new UDPSocket(sockfd));
    }
    else
    {
        spdlog::error("SocketHelpers::createUDPSocket, error={0}", sockfd);
        return nullptr;
    }
}

//
// Created by qazer on 04.04.2019.
//

#ifndef NETWORK_UDPSOCKET_H
#define NETWORK_UDPSOCKET_H

#include <memory>
#include <sys/socket.h>
#include <spdlog/spdlog.h>
#include "SocketAddress.h"


class UDPSocket {
public:
    void Bind(SocketAddress address);
    void ReceiveFrom();
private:
    int mSocket;
};

typedef std::shared_ptr<UDPSocket> UDPSocketPtr;

#endif //NETWORK_UDPSOCKET_H

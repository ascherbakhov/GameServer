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
    int ReceiveFrom(void*, int, SocketAddress&);
    void SetNonBlockingMode(bool isNonBlocking);
    void Close();
private:
    explicit UDPSocket(int socket) : mSocket(socket){};
    int mSocket;
    friend class SocketHelpers;
};

typedef std::shared_ptr<UDPSocket> UDPSocketPtr;

#endif //NETWORK_UDPSOCKET_H

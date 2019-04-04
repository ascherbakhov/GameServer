//
// Created by qazer on 04.04.2019.
//

#ifndef NETWORK_UDPSOCKET_H
#define NETWORK_UDPSOCKET_H

#include <memory>
#include <sys/socket.h>
#include <spdlog/spdlog.h>
#include "NetworkInterface.h"


class UDPSocket {
public:
    int Bind(NetworkInterface address);
    int ReceiveFrom(void*, int, NetworkInterface&);
    int Close();
    void SetNonBlockingMode(bool isNonBlocking);
private:
    explicit UDPSocket(int socket) : mSocket(socket){};
    int mSocket;
    friend class SocketHelpers;
};

typedef std::shared_ptr<UDPSocket> UDPSocketPtr;

#endif //NETWORK_UDPSOCKET_H

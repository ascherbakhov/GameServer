//
// Created by qazer on 04.04.2019.
//

#ifndef NETWORK_SOCKETHELPERS_H
#define NETWORK_SOCKETHELPERS_H

#include "sys/socket.h"
#include "../../third-party/spdlog/include/spdlog/spdlog.h"
#include "UDPSocket.h"


class SocketHelpers {
public:
    static UDPSocketPtr createUDPSocket();
};

#endif //NETWORK_SOCKETHELPERS_H

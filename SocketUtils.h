//
// Created by qazer on 04.04.2019.
//

#ifndef NETWORK_SOCKETUTILS_H
#define NETWORK_SOCKETUTILS_H

#include "sys/socket.h"
#include "spdlog/spdlog.h"
#include "UDPSocket.h"


class SocketUtils {
    UDPSocketPtr createUDPSocket();
};


#endif //NETWORK_SOCKETUTILS_H

//
// Created by qazer on 04.04.2019.
//

#ifndef NETWORK_SOCKETADDRESS_H
#define NETWORK_SOCKETADDRESS_H


#include <bits/socket.h>
#include <string>


class SocketAddress {
public:
    SocketAddress(const char *ip_addr, u_int16_t port);
    sockaddr* Get();
    size_t Size();
private:
    sockaddr* mAddress;
};


#endif //NETWORK_SOCKETADDRESS_H

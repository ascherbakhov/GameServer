//
// Created by qazer on 04.04.2019.
//

#ifndef NETWORK_SOCKETADDRESS_H
#define NETWORK_SOCKETADDRESS_H


#include <bits/socket.h>
#include <string>
#include <netinet/in.h>

class SocketAddress {
public:
    SocketAddress(const char* ip_addr, u_int16_t port);
    SocketAddress(const sockaddr_in&);
    SocketAddress() {memset(&mAddress, 0, sizeof(sockaddr_in));}
    size_t Size();
    sockaddr* Get();
private:
    sockaddr_in mAddress;
};


#endif //NETWORK_SOCKETADDRESS_H

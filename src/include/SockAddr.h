//
// Created by qazer on 04.04.2019.
//

#ifndef NETWORK_SOCKADDR_H
#define NETWORK_SOCKADDR_H


#include <bits/socket.h>
#include <string>
#include <netinet/in.h>

class SockAddr {
public:
    SockAddr(const char* ip_addr, u_int16_t port);
    SockAddr(const sockaddr_in&);
    SockAddr() {memset(&mAddress, 0, sizeof(sockaddr_in));}
    size_t Size();
    sockaddr* Get();
private:
    sockaddr_in mAddress;
};


#endif //NETWORK_SOCKADDR_H

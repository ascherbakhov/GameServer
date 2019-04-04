//
// Created by qazer on 04.04.2019.
//

#ifndef NETWORK_NETWORKINTERFACE_H
#define NETWORK_NETWORKINTERFACE_H


#include <bits/socket.h>
#include <string>
#include <netinet/in.h>

class NetworkInterface {
public:
    NetworkInterface(const char* ip_addr, u_int16_t port);
    NetworkInterface(const sockaddr_in&);
    NetworkInterface() {memset(&mAddress, 0, sizeof(sockaddr_in));}
    size_t Size();
    sockaddr* Get();
private:
    sockaddr_in mAddress;
};


#endif //NETWORK_NETWORKINTERFACE_H

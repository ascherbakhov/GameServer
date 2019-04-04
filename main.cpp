#include <iostream>
#include <cstring>
#include "sys/socket.h"
#include "arpa/inet.h"
#include "SocketAddress.h"
#include "UDPSocket.h"
#include "SocketHelpers.h"


int main() {
    char data[9000];
    SocketAddress address{"127.0.0.1", 43000};
    UDPSocketPtr socket = SocketHelpers::createUDPSocket();
    socket->SetNonBlockingMode(true);
    socket->Bind(address);
    SocketAddress inSockAddress;
    int bytesNum = socket->ReceiveFrom(data, 9000, inSockAddress);
    socket->Close();
    return 0;
}
#include <iostream>
#include <cstring>
#include "sys/socket.h"
#include "arpa/inet.h"
#include "NetworkInterface.h"
#include "UDPSocket.h"
#include "SocketHelpers.h"


int main() {
    int bufferLen  = 900;
    char data[bufferLen];
    NetworkInterface address{"127.0.0.1", 43000};
    UDPSocketPtr socket = SocketHelpers::createUDPSocket();
    socket->SetNonBlockingMode(true);
    socket->Bind(address);
    NetworkInterface inSockAddress;
    int bytesNum = socket->ReceiveFrom(data, bufferLen, inSockAddress);
    socket->Close();
    return 0;
}
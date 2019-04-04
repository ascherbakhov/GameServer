//
// Created by qazer on 04.04.2019.
//

#include <spdlog/spdlog.h>
#include "UDPSocket.h"

int UDPSocket::Bind(NetworkInterface address)
{
    int err = bind(mSocket, address.Get(), address.Size());
    if (err != 0)
    {
        spdlog::error("UDPSocket::Bind: {0}", strerror(errno));
    }
    return err;
}


int UDPSocket::ReceiveFrom(void* buffer, int len, NetworkInterface& fromAddr)
{
    socklen_t fromLen = fromAddr.Size();
    int bytesNum = recvfrom(mSocket,
            static_cast<char*>(buffer),
            len,
            0,
            fromAddr.Get(),
            &fromLen);
    if (errno != EAGAIN)
    {
        spdlog::error("Error reading from socket: {}", strerror(errno));
    }
        return bytesNum;
}

void UDPSocket::SetNonBlockingMode(bool isNonBlocking) {
    int flags = fcntl(mSocket, F_GETFL, 0);
    flags = isNonBlocking ? (flags | O_NONBLOCK) : (flags & ~O_NONBLOCK);
    fcntl(mSocket, F_SETFL, flags);
}

int UDPSocket::Close() {
    int err = close(mSocket);
    if (err)
    {
        spdlog::error("Error while closing socket, errno={0}", strerror(errno));
    }
    return err;
}

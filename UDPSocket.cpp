//
// Created by qazer on 04.04.2019.
//

#include <spdlog/spdlog.h>
#include "UDPSocket.h"

void UDPSocket::Bind(SocketAddress address)
{
    int err = bind(mSocket, address.Get(), address.Size());
    if (err != 0)
    {
        spdlog::error("UDPSocket::Bind: {0}", strerror(errno));
        exit(err); //TODO: remove with correct exiting
    }
}


int UDPSocket::ReceiveFrom(void* buffer, int len, SocketAddress& fromAddr)
{
    socklen_t fromLen = fromAddr.Size();
    int bytesNum = recvfrom(mSocket,
            static_cast<char*>(buffer),
            len,
            0,
            fromAddr.Get(),
            &fromLen);
    if (bytesNum >=0)
    {
        return bytesNum;
    }
    else if (errno == EAGAIN)
    {
        spdlog::error("Blocking operation, repeat later");
        return -1;
    }
    else
    {
        spdlog::error("Error reading from socket: {}", strerror(errno));
        return -1;
    }

}

void UDPSocket::SetNonBlockingMode(bool isNonBlocking) {
    int flags = fcntl(mSocket, F_GETFL, 0);
    flags = isNonBlocking ? (flags | O_NONBLOCK) : (flags & ~O_NONBLOCK);
    fcntl(mSocket, F_SETFL, flags);
}

void UDPSocket::Close() {
    if (close(mSocket))
    {
        spdlog::error("Error while closing socket, errno={0}", strerror(errno));
    }
}

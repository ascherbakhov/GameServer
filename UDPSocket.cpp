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
        spdlog::error("UDPSocket::Bind: {0}", strerror(err));
        exit(err);
    }
}


void UDPSocket::ReceiveFrom()
{
}
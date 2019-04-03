#include <iostream>
#include <cstring>
#include "sys/socket.h"
#include "arpa/inet.h"


int main() {
    struct sockaddr_in addr{};
    memset(&addr, 0, sizeof(addr));
    addr.sin_family = AF_INET;
    addr.sin_port = 43000;
    inet_pton(AF_INET, "127.0.0.1", &addr.sin_addr.s_addr);

    int fdsock = socket(AF_INET, SOCK_DGRAM, 0);
    int error = bind(fdsock, reinterpret_cast<struct sockaddr *>(&addr), sizeof(addr));
    if (error)
    {
            std::cout << "Error binding addr for socket!" << std::endl;
    }


    return 0;
}
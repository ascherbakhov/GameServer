//
// Created by qazer on 04.04.2019.
//

#include "SocketUtils.h"

void SocketUtils::createUDPSocket() {
    int s = socket(AF_INET, SOCK_DGRAM, 0);
}

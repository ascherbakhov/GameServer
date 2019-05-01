//
// Created by qazzer on 01.05.2019.
//

#include "Entities/Enemy.h"

void Enemy::Write(OutputBitStream &outputBitStream) {
    outputBitStream.Write(mHealth);
}

//
// Created by qazzer on 01.05.2019.
//

#include "Entities/Vehicle.h"

void Vehicle::Write(OutputBitStream &outputBitStream) {
    outputBitStream.Write(mSpeed);
}

#pragma once

#include <cstdint>
#include "bitutils.hpp"

const uint64_t NORTH_A1      = 0x0101010101010100;
const uint64_t SOUTH_H8      = 0x0080808080808080;
const uint64_t NORTH_EAST_A1 = 0x8040201008040200;
const uint64_t NORTH_WEST_H1 = 0x0102040810204000;
const uint64_t SOUTH_EAST_A8 = 0x0002040810204080;
const uint64_t SOUTH_WEST_H8 = 0x0040201008040201;

enum Direction {
    NORTH, SOUTH, EAST, WEST, NORTH_EAST, NORTH_WEST, SOUTH_EAST, SOUTH_WEST
};

extern uint64_t rays[8][64];
void initRays();

#include <cstdint>

const uint64_t NORTH_A1      = 0x0101010101010100;
const uint64_t SOUTH_H8      = 0x0080808080808080;
const uint64_t NORTH_EAST_A1 = 0x8040201008040200;


enum Direction {
    NORTH, SOUTH, EAST, WEST, NORTH_EAST, NORTH_WEST, SOUTH_EAST, SOUTH_WEST
};

extern uint64_t rays[8][64];

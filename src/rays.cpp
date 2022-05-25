#include "rays.hpp"
#include "movegen.hpp"

uint64_t rays[8][64];  // Contains squares for all directions

void initRays() {
    for (int sq = 0; sq < 64; sq++) {
        // North
        rays[NORTH][sq] = NORTH_A1 << sq;
        // South
        rays[SOUTH][sq] = SOUTH_H8 >> (63 - sq);
        // East
        rays[EAST][sq] = 2 * ((uint64_t)0x1 << (sq | 7)) - ((uint64_t)0x1 << sq);
        // West 
        rays[WEST][sq] = ((uint64_t)0x1 << sq) - (((uint64_t)0x1 << (sq & 56)));
        
        uint64_t coolBb = rays[NORTH][sq] | rays[SOUTH][sq] | rays[EAST][sq] | rays[WEST][sq];
        std::cout << prettyPrintBitboard(coolBb) << "\n";
    }
}
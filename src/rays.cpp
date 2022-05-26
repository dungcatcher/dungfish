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
        rays[EAST][sq] = 2 * ( ((uint64_t)0x1 << (sq | 7)) - ((uint64_t)0x1 << sq) );
        // West 
        rays[WEST][sq] = ((uint64_t)0x1 << sq) - (((uint64_t)0x1 << (sq & 56)));
    }

    uint64_t noEa = NORTH_EAST_A1;
    uint64_t noWe = NORTH_WEST_H1;
    uint64_t soEa = SOUTH_EAST_A8;
    uint64_t soWe = SOUTH_WEST_H8;
    for (int f = 0; f < 8; f++, noEa = eastOne(noEa), noWe = westOne(noWe), soEa = eastOne(soEa), soWe = westOne(soWe)) {
        uint64_t ne = noEa;
        uint64_t nw = noWe;
        uint64_t se = soEa;
        uint64_t sw = soWe;
        for (int r8 = 0; r8 < 64; r8 += 8, ne <<= 8, nw <<= 8, se >>= 8, sw >>= 8) {
            rays[NORTH_EAST][r8 + f] = ne;
            rays[NORTH_WEST][r8 + (7 - f)] = nw;
            rays[SOUTH_EAST][(56 - r8) + f] = se;
            rays[SOUTH_WEST][(56 - r8) + (7 - f)] = sw;
        }
    }


    for (int sq = 0; sq < 64; sq++) {
        uint64_t coolBb = rays[NORTH][sq] | rays[SOUTH][sq] | rays[EAST][sq] | rays[WEST][sq] | rays[NORTH_EAST][sq] | rays[NORTH_WEST][sq] | rays[SOUTH_EAST][sq] | rays[SOUTH_WEST][sq];
        std::cout << prettyPrintBitboard(coolBb) << "\n";
    }
}
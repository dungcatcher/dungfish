#include "tables.hpp"
#include "bitutils.hpp"
#include "movegen.hpp"

uint64_t knightAttacks[64];
uint64_t kingAttacks[64];

void initKnightAttacks() {
    for (int sq = 0; sq < 64; sq++) {
        uint64_t sqBb, east, west, attacks;
        sqBb = (uint64_t)0x1 << sq; // Square bitboard
        east = eastOne(sqBb); // One square out 
        west = westOne(sqBb);
        attacks = (east | west) << 16; // Top and bottom leaps
        attacks |= (east | west) >> 16;
        east = eastOne(east); // Two squares out
        west = westOne(west);
        attacks |= (east | west) << 8; // Left and right leaps
        attacks |= (east | west) >> 8;

        knightAttacks[sq] = attacks;
    }
}

void initKingAttacks() {
    for (int sq = 0; sq < 64; sq++) {
        uint64_t sqBb = (uint64_t)0x1 << sq;
        uint64_t attacks = eastOne(sqBb) | westOne(sqBb);
        sqBb |= attacks;
        attacks |= nortOne(sqBb) | soutOne(sqBb);

        kingAttacks[sq] = attacks;
    }
}

void initTables() {
    initKnightAttacks();
    initKingAttacks();
}
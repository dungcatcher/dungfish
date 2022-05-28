#pragma once

#include <cstdint>

extern uint64_t knightAttacks[64];
extern uint64_t bishopAttacks[64];

void initKnightAttacks();
void initBishopAttacks();
void initTables();
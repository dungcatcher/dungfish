#include <cstdint>
#include <bitset>
#include <iostream>
#include <vector>

struct Move {
    unsigned int start; // Number from 0-63 (lerf)
    unsigned int end;
    unsigned int flags; // See: https://www.chessprogramming.org/Encoding_Moves#Information_Required
};

std::string prettyPrintBitboard(uint64_t bb);

void addMove(unsigned int start, unsigned int end, unsigned int flags, Move* moves);

uint64_t wSinglePushTargets(uint64_t wpawns, uint64_t empty);
uint64_t wDblPushTargets(uint64_t wpawns, uint64_t empty);
uint64_t bSinglePushTargets(uint64_t bpawns, uint64_t empty);
uint64_t bDblPushTargets(uint64_t bpawns, uint64_t empty);
uint64_t wPawnsAble2Push(uint64_t wpawns, uint64_t empty);
uint64_t wPawnsAble2DblPush(uint64_t wpawns, uint64_t empty);
uint64_t bPawnsAble2Push(uint64_t bpawns, uint64_t empty);
uint64_t bPawnsAble2DblPush(uint64_t bpawns, uint64_t empty);

uint64_t wPawnEastAttacks(uint64_t wpawns);
uint64_t wPawnWestAttacks(uint64_t wpawns);
uint64_t wPawnAnyAttacks(uint64_t wpawns);
uint64_t bPawnEastAttacks(uint64_t bpawns);
uint64_t bPawnWestAttacks(uint64_t bpawns);
uint64_t bPawnAnyAttacks(uint64_t bpawns);
uint64_t wPawnsAble2CaptureEast(uint64_t wpawns, uint64_t bpawns);
uint64_t wPawnsAble2CaptureWest(uint64_t wpawns, uint64_t bpawns);
uint64_t wPawnsAble2CaptureAny(uint64_t wpawns, uint64_t bpieces);
uint64_t bPawnsAble2CaptureEast(uint64_t bpawns, uint64_t wpieces);
uint64_t bPawnsAble2CaptureWest(uint64_t bpawns, uint64_t wpieces);
uint64_t bPawnsAble2CaptureAny(uint64_t bpawns, uint64_t wpieces);

void generatePawnMoves(std::vector<Move>& moveList, bool isWhite, uint64_t pawns, uint64_t oppPieces, uint64_t empty);
void generateKnightMoves(std::vector<Move> &moveList, uint64_t knights, uint64_t teamPieces);
#include <cstdint>
#include <bitset>
#include <iostream>
#include <vector>

struct Move {
    unsigned int start; // Number from 0-63 (lerf)
    unsigned int end;
    unsigned int flags; // See: https://www.chessprogramming.org/Encoding_Moves#Information_Required
};

const uint64_t notAFile = 0xfefefefefefefefe; // ~0x0101010101010101
const uint64_t notHFile = 0x7f7f7f7f7f7f7f7f; // ~0x8080808080808080

std::string prettyPrintBitboard(uint64_t bb);

uint64_t soutOne (uint64_t b);
uint64_t nortOne (uint64_t b);
uint64_t eastOne (uint64_t b);
uint64_t noEaOne (uint64_t b);
uint64_t soEaOne (uint64_t b);
uint64_t westOne (uint64_t b);
uint64_t soWeOne (uint64_t b);
uint64_t noWeOne (uint64_t b);

const int index64[64] = {
    0, 47,  1, 56, 48, 27,  2, 60,
   57, 49, 41, 37, 28, 16,  3, 61,
   54, 58, 35, 52, 50, 42, 21, 44,
   38, 32, 29, 23, 17, 11,  4, 62,
   46, 55, 26, 59, 40, 36, 15, 53,
   34, 51, 20, 43, 31, 22, 10, 45,
   25, 39, 14, 33, 19, 30,  9, 24,
   13, 18,  8, 12,  7,  6,  5, 63
};

/**
 * bitScanForward
 * @author Kim Walisch (2012)
 * @param bb bitboard to scan
 * @precondition bb != 0
 * @return index (0..63) of least significant one bit
 */
int bitScanForward(uint64_t bb);

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
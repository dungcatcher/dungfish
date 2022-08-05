#pragma once

#include <cstdint>
#include <bitset>
#include <iostream>
#include <vector>
#include <map>

#include "rays.hpp"
#include "board.hpp"

class Board;
struct Move {
    unsigned int start; // Number from 0-63 (lerf)
    unsigned int end;
    unsigned int flags; // See: https://www.chessprogramming.org/Encoding_Moves#Information_Required
};
std::string getMoveString(Move move);

inline std::string coordinateIndexTable[64] {
    "a1", "b1", "c1", "d1", "e1", "f1", "g1", "h1",
    "a2", "b2", "c2", "d2", "e2", "f2", "g2", "h2",
    "a3", "b3", "c3", "d3", "e3", "f3", "g3", "h3",
    "a4", "b4", "c4", "d4", "e4", "f4", "g4", "h4",
    "a5", "b5", "c5", "d5", "e5", "f5", "g5", "h5",
    "a6", "b6", "c6", "d6", "e6", "f6", "g6", "h6",
    "a7", "b7", "c7", "d7", "e7", "f7", "g7", "h7",
    "a8", "b8", "c8", "d8", "e8", "f8", "g8", "h8",
};

inline std::map<std::string, int> coordinateIndexMap {
    {"a1", 0 }, {"b1", 1 }, {"c1", 2 }, {"d1", 3 }, {"e1", 4 }, {"f1", 5 }, {"g1", 6 }, {"h1", 7 }, 
    {"a2", 8 }, {"b2", 9 }, {"c2", 10}, {"d2", 11}, {"e2", 12}, {"f2", 13}, {"g2", 14}, {"h2", 15}, 
    {"a3", 16}, {"b3", 17}, {"c3", 18}, {"d3", 19}, {"e3", 20}, {"f3", 21}, {"g3", 22}, {"h3", 23}, 
    {"a4", 24}, {"b4", 25}, {"c4", 26}, {"d4", 27}, {"e4", 28}, {"f4", 29}, {"g4", 30}, {"h4", 31}, 
    {"a5", 32}, {"b5", 33}, {"c5", 34}, {"d5", 35}, {"e5", 36}, {"f5", 37}, {"g5", 38}, {"h5", 39}, 
    {"a6", 40}, {"b6", 41}, {"c6", 42}, {"d6", 43}, {"e6", 44}, {"f6", 45}, {"g6", 46}, {"h6", 47}, 
    {"a7", 48}, {"b7", 49}, {"c7", 50}, {"d7", 51}, {"e7", 52}, {"f7", 53}, {"g7", 54}, {"h7", 55}, 
    {"a8", 56}, {"b8", 57}, {"c8", 58}, {"d8", 59}, {"e8", 60}, {"f8", 61}, {"g8", 62}, {"h8", 63}
};

std::string prettyPrintBitboard(uint64_t bb);

void addMove(unsigned int start, unsigned int end, unsigned int flags, Move* moveList);
void addPromotion(unsigned int start, unsigned int end, unsigned int flags, Move* moveList);  // Flags for capturing
inline unsigned int promotionPieces[4] = { 0x0, 0x1, 0x2, 0x3 };

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
uint64_t wPawnsAble2CaptureEast(uint64_t wpawns, uint64_t bpieces);
uint64_t wPawnsAble2CaptureWest(uint64_t wpawns, uint64_t bpieces);
uint64_t wPawnsAble2CaptureAny(uint64_t wpawns, uint64_t bpieces);
uint64_t bPawnsAble2CaptureEast(uint64_t bpawns, uint64_t wpieces);
uint64_t bPawnsAble2CaptureWest(uint64_t bpawns, uint64_t wpieces);
uint64_t bPawnsAble2CaptureAny(uint64_t bpawns, uint64_t wpieces);

uint64_t getPositiveRayAttacks(uint64_t occupied, int square, Direction dir);
uint64_t getNegativeRayAttacks(uint64_t occupied, int square, Direction dir);

uint64_t generateBishopAttacks(uint64_t blockers, int square);
uint64_t generateRookAttacks(uint64_t blockers, int square);
uint64_t generateQueenAttacks(uint64_t blockers, int square);

class Board;
void generatePawnMoves(std::vector<Move> &moveList, const Board& board);
void generateKnightMoves(std::vector<Move> &moveList, const Board& board);
void generateBishopMoves(std::vector<Move> &moveList, const Board& board);
void generateRookMoves(std::vector<Move> &moveList, const Board& board);
void generateQueenMoves(std::vector<Move> &moveList, const Board& board);
void generateKingMoves(std::vector<Move> &moveList, const Board& board);

std::vector<Move> generateLegalMoves(std::vector<Move> &moveList, const Board& board);

int perft(int depth, Board board, bool Root);
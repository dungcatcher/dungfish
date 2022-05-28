#pragma once

#include <cstdint>
#include <bitset>
#include <iostream>
#include <vector>

#include "rays.hpp"

struct Move {
    unsigned int start; // Number from 0-63 (lerf)
    unsigned int end;
    unsigned int flags; // See: https://www.chessprogramming.org/Encoding_Moves#Information_Required
};

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

uint64_t getPositiveRayAttacks(uint64_t occupied, int square, Direction dir);
uint64_t getNegativeRayAttacks(uint64_t occupied, int square, Direction dir);

uint64_t generateBishopAttacks(uint64_t blockers, int square);
uint64_t generateRookAttacks(uint64_t blockers, int square);
uint64_t generateQueenAttacks(uint64_t blockers, int square);
void generateBishopMoves(std::vector<Move> &moveList, uint64_t bishops, uint64_t teamPieces, uint64_t enemyPieces);
void generateRookMoves(std::vector<Move> &moveList, uint64_t rooks, uint64_t teamPieces, uint64_t enemyPieces);
void generateQueenMoves(std::vector<Move> &moveList, uint64_t queens, uint64_t teamPieces, uint64_t enemyPieces);
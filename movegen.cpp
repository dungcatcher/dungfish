#include "movegen.hpp"

// Start & End (Lerf (0, 63)), flags see: https://www.chessprogramming.org/Encoding_Moves#Information_Required
Move::Move(unsigned int start, unsigned int end, unsigned int flags) {
   this->start = start;
   this->end = end;
   this->flags = flags;
}

uint64_t soutOne (uint64_t b) {return  b >> 8;}
uint64_t nortOne (uint64_t b) {return  b << 8;}
uint64_t eastOne (uint64_t b) {return (b << 1) & notAFile;}
uint64_t noEaOne (uint64_t b) {return (b << 9) & notAFile;}
uint64_t soEaOne (uint64_t b) {return (b >> 7) & notAFile;}
uint64_t westOne (uint64_t b) {return (b >> 1) & notHFile;}
uint64_t soWeOne (uint64_t b) {return (b >> 9) & notHFile;}
uint64_t noWeOne (uint64_t b) {return (b << 7) & notHFile;}

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
int bitScanForward(uint64_t bb) {
   const uint64_t debruijn64 = 0x03f79d71b4cb0a89;
   return index64[((bb ^ (bb-1)) * debruijn64) >> 58];
}

// Pawns

uint64_t wSinglePushTargets(uint64_t wpawns, uint64_t empty) {
   return nortOne(wpawns) & empty;
}

uint64_t wDblPushTargets(uint64_t wpawns, uint64_t empty) {
   const uint64_t rank4 = 0x00000000FF000000;
   uint64_t singlePushs = wSinglePushTargets(wpawns, empty);
   return nortOne(singlePushs) & empty & rank4;
}

uint64_t bSinglePushTargets(uint64_t bpawns, uint64_t empty) {
   return soutOne(bpawns) & empty;
}

uint64_t bDoublePushTargets(uint64_t bpawns, uint64_t empty) {
   const uint64_t rank5 = 0x000000FF00000000;
   uint64_t singlePushs = bSinglePushTargets(bpawns, empty);
   return soutOne(singlePushs) & empty & rank5;
}

uint64_t wPawnsAble2Push(uint64_t wpawns, uint64_t empty) {
   return soutOne(empty) & wpawns;
}

uint64_t wPawnsAble2DblPush(uint64_t wpawns, uint64_t empty) {
   const uint64_t rank4 = 0x00000000FF000000;
   uint64_t emptyRank3 = soutOne(empty & rank4) & empty;
   return wPawnsAble2Push(wpawns, emptyRank3);
}

void generateWPawnMoves(uint64_t wpawns, uint64_t empty) {
   uint64_t wSinglePushPawns = wPawnsAble2Push(wpawns, empty);
   while (wSinglePushPawns != 0) {
      int idx = bitScanForward(wSinglePushPawns); // Index of the first least significant 1 bit
      uint64_t wPawnBb = (uint64_t)0x1 << idx; // Bitboard containing the current pawn
      uint64_t wPawnTarget = wSinglePushTargets(wPawnBb, empty);
      int targetIdx = bitScanForward(wPawnTarget);
      Move move(idx, targetIdx, 0x0);
      std::cout << move.start << " " << move.end << " " << move.flags << "\n";

      wSinglePushPawns &= ~(wPawnBb); // Set that bit to 0
   }
   uint64_t wDoublePushPawns = wPawnsAble2DblPush(wpawns, empty);
   while (wDoublePushPawns != 0) {
      int idx = bitScanForward(wDoublePushPawns);
      uint64_t wPawnBb = (uint64_t)0x1 << idx;
      uint64_t wPawnTarget = wDblPushTargets(wPawnBb, empty);
      int targetIdx = bitScanForward(wPawnTarget);
      Move move(idx, targetIdx, 0x0);
      std::cout << move.start << " " << move.end << " " << move.flags << "\n";

      wDoublePushPawns &= ~(wPawnBb);
   }
}

void generateBPawnMoves(uint64_t bpawns, uint64_t empty) {
   uint64_t bSinglePushPawns = wPawnsAble2Push(bpawns, empty);
   while (bSinglePushPawns != 0) {
      int idx = bitScanForward(bSinglePushPawns); // Index of the first least significant 1 bit
      uint64_t bPawnBb = (uint64_t)0x1 << idx; // Bitboard containing the current pawn
      uint64_t bPawnTarget = wSinglePushTargets(bPawnBb, empty);
      int targetIdx = bitScanForward(bPawnTarget);
      Move move(idx, targetIdx, 0x0);
      std::cout << move.start << " " << move.end << " " << move.flags << "\n";

      bSinglePushPawns &= ~(bPawnBb); // Set that bit to 0
   }
   uint64_t bDoublePushPawns = wPawnsAble2DblPush(bpawns, empty);
   while (bDoublePushPawns != 0) {
      int idx = bitScanForward(bDoublePushPawns);
      uint64_t bPawnBb = (uint64_t)0x1 << idx;
      uint64_t bPawnTarget = wDblPushTargets(bPawnBb, empty);
      int targetIdx = bitScanForward(bPawnTarget);
      Move move(idx, targetIdx, 0x0);
      std::cout << move.start << " " << move.end << " " << move.flags << "\n";

      bDoublePushPawns &= ~(bPawnBb);
   }
}
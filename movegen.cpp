#include "movegen.hpp"

uint64_t soutOne (uint64_t b) {return  b >> 8;}
uint64_t nortOne (uint64_t b) {return  b << 8;}
uint64_t eastOne (uint64_t b) {return (b << 1) & notAFile;}
uint64_t noEaOne (uint64_t b) {return (b << 9) & notAFile;}
uint64_t soEaOne (uint64_t b) {return (b >> 7) & notAFile;}
uint64_t westOne (uint64_t b) {return (b >> 1) & notHFile;}
uint64_t soWeOne (uint64_t b) {return (b >> 9) & notHFile;}
uint64_t noWeOne (uint64_t b) {return (b << 7) & notHFile;}

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
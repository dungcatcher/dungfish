#include "bitutils.hpp"

uint64_t soutOne (uint64_t b) {return  b >> 8;}
uint64_t nortOne (uint64_t b) {return  b << 8;}
uint64_t eastOne (uint64_t b) {return (b & notHFile) << 1;}
uint64_t noEaOne (uint64_t b) {return (b & notHFile) << 9;}
uint64_t soEaOne (uint64_t b) {return (b & notHFile) >> 7;}
uint64_t westOne (uint64_t b) {return (b & notAFile) >> 1;}
uint64_t soWeOne (uint64_t b) {return (b & notAFile) >> 9;}
uint64_t noWeOne (uint64_t b) {return (b & notAFile) << 7;}

int bitScanForward(uint64_t bb) {
	const uint64_t debruijn64 = 0x03f79d71b4cb0a89;
	return index64[((bb ^ (bb-1)) * debruijn64) >> 58];
}

int bitScanReverse(uint64_t bb) {
	const uint64_t debruijn64 = 0x03f79d71b4cb0a89;
	bb |= bb >> 1; 
	bb |= bb >> 2;
	bb |= bb >> 4;
	bb |= bb >> 8;
	bb |= bb >> 16;
	bb |= bb >> 32;
	return index64[(bb * debruijn64) >> 58];
}


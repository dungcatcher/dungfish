#include "movegen.hpp"

// void prettyPrintBitboard(uint64_t bb) {
// 	std::bitset<64> bitset(bb);
// 	std::string binaryString = bitset.to_string();
// 	for (int i = 0; i < binaryString.length(); i++) {
// 		std::cout << binaryString[i];
// 		if (i % 8 == 0 && i != 0) {
// 			std::cout << "\n";
// 		}
// 	}
// 	std::cout << "\n";
// }

uint64_t soutOne (uint64_t b) {return  b >> 8;}
uint64_t nortOne (uint64_t b) {return  b << 8;}
uint64_t eastOne (uint64_t b) {return (b << 1) & notAFile;}
uint64_t noEaOne (uint64_t b) {return (b << 9) & notAFile;}
uint64_t soEaOne (uint64_t b) {return (b >> 7) & notAFile;}
uint64_t westOne (uint64_t b) {return (b >> 1) & notHFile;}
uint64_t soWeOne (uint64_t b) {return (b >> 9) & notHFile;}
uint64_t noWeOne (uint64_t b) {return (b << 7) & notHFile;}

int bitScanForward(uint64_t bb) {
	const uint64_t debruijn64 = 0x03f79d71b4cb0a89;
	return index64[((bb ^ (bb-1)) * debruijn64) >> 58];
}

void addMove(unsigned int start, unsigned int end, unsigned int flags, std::vector<Move>& moveList) {
	Move move;
	move.start = start;
	move.end = end;
	move.flags = flags;
	moveList.push_back(move);
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

uint64_t bDblPushTargets(uint64_t bpawns, uint64_t empty) {
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

uint64_t bPawnsAble2Push(uint64_t bpawns, uint64_t empty) {
	return nortOne(empty) & bpawns;
}

uint64_t bPawnsAble2DblPush(uint64_t bpawns, uint64_t empty) {
	const uint64_t rank5 = 0x000000FF000000;
	uint64_t emptyRank6 = nortOne(empty & rank5) & empty;
	return wPawnsAble2Push(bpawns, emptyRank6);
}

void generatePawnMoves(std::vector<Move> &moveList, bool isWhite, uint64_t pawns, uint64_t empty) {
	std::cout << "heheha" << "\n";
	uint64_t singlePushPawns = isWhite ? (wPawnsAble2Push(pawns, empty)) : (bPawnsAble2Push(pawns, empty));
	while (singlePushPawns != 0) {
		int idx = bitScanForward(singlePushPawns); // Index of the first least significant 1 bit
		uint64_t pawnBb = (uint64_t)0x1 << idx; // Bitboard containing the current pawn
		// prettyPrintBitboard(pawnBb);
		uint64_t pawnTarget = isWhite ? (wSinglePushTargets(pawnBb, empty)) : (bSinglePushTargets(pawnBb, empty));
		int targetIdx = bitScanForward(pawnTarget);
		std::cout << idx << "to" << targetIdx << "\n"; 
		addMove(idx, targetIdx, 0x0, moveList);

		singlePushPawns &= ~(pawnBb); // Set that bit to 0
	}
	uint64_t dblPushPawns = isWhite ? (wPawnsAble2DblPush(pawns, empty)) : (bPawnsAble2DblPush(pawns, empty));
	while (dblPushPawns != 0) {
		int idx = bitScanForward(dblPushPawns);
		uint64_t pawnBb = (uint64_t)0x1 << idx;
		uint64_t pawnTarget = isWhite ? (wDblPushTargets(pawnBb, empty)) : (bDblPushTargets(pawnBb, empty));
		int targetIdx = bitScanForward(pawnTarget);
		std::cout << idx << "to" << targetIdx << "\n"; 
		addMove(idx, targetIdx, 0x0, moveList);

		dblPushPawns &= ~(pawnBb);
	}
}
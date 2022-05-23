#include "movegen.hpp"

std::string prettyPrintBitboard(uint64_t bb) {
	std::bitset<64> bitset(bb);
	std::string binaryString = bitset.to_string();
	std::string splitBinaryString = "";
	for (int i = 0; i < binaryString.length(); i++) {
		splitBinaryString += binaryString[i];
		if ((i + 1) % 8 == 0)
			splitBinaryString += '\n';
	}

	return splitBinaryString;
}

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


uint64_t wPawnEastAttacks(uint64_t wpawns) {return noEaOne(wpawns);}
uint64_t wPawnWestAttacks(uint64_t wpawns) {return noWeOne(wpawns);}
uint64_t wPawnAnyAttacks(uint64_t wpawns) {
   return wPawnEastAttacks(wpawns) | wPawnWestAttacks(wpawns);
}

uint64_t bPawnEastAttacks(uint64_t bpawns) {return soEaOne(bpawns);}
uint64_t bPawnWestAttacks(uint64_t bpawns) {return soWeOne(bpawns);}
uint64_t bPawnAnyAttacks(uint64_t bpawns) {
   return bPawnEastAttacks(bpawns) | bPawnWestAttacks(bpawns);
}

uint64_t wPawnsAble2CaptureEast(uint64_t wpawns, uint64_t bpawns) {
   return wpawns & bPawnWestAttacks(bpawns);
}
uint64_t wPawnsAble2CaptureWest(uint64_t wpawns, uint64_t bpawns) {
   return wpawns & bPawnEastAttacks(bpawns);
}
uint64_t wPawnsAble2CaptureAny(uint64_t wpawns, uint64_t bpawns) {
   return wpawns & bPawnAnyAttacks(bpawns);
}
uint64_t bPawnsAble2CaptureEast(uint64_t bpawns, uint64_t wpawns) {
   return bpawns & wPawnWestAttacks(wpawns);
}
uint64_t bPawnsAble2CaptureWest(uint64_t bpawns, uint64_t wpawns) {
   return bpawns & wPawnEastAttacks(wpawns);
}
uint64_t bPawnsAble2CaptureAny(uint64_t bpawns, uint64_t wpawns) {
   return bpawns & wPawnAnyAttacks(wpawns);
}


void generatePawnMoves(std::vector<Move> &moveList, bool isWhite, uint64_t pawns, uint64_t oppPawns, uint64_t empty) {
	// Pawn pushes
	uint64_t singlePushPawns = isWhite ? (wPawnsAble2Push(pawns, empty)) : (bPawnsAble2Push(pawns, empty));
	uint64_t singlePushTargets = isWhite ? (wSinglePushTargets(singlePushPawns, empty)) : (bSinglePushTargets(singlePushPawns, empty));
	while (singlePushTargets != 0) { // Loop through 1 bits of target squares
		int endSquare = bitScanForward(singlePushTargets); 
		int fromSquare = endSquare + (isWhite ? -8 : 8); // Trace back to origin square
		addMove(fromSquare, endSquare, 0x0, moveList);

		singlePushTargets &= singlePushTargets - 1; // Set ls1b to 0
	}

	uint64_t dblPushPawns = isWhite ? (wPawnsAble2DblPush(pawns, empty)) : (bPawnsAble2DblPush(pawns, empty));
	uint64_t dblPushTargets = isWhite ? (wDblPushTargets(dblPushPawns, empty)) : (bDblPushTargets(dblPushPawns, empty));
	while (dblPushTargets != 0) {
		int endSquare = bitScanForward(dblPushTargets); 
		int fromSquare = endSquare + (isWhite ? -16 : 16);
		addMove(fromSquare, endSquare, 0x1, moveList);

		dblPushTargets &= dblPushTargets - 1;
	}

	// Captures
	uint64_t capturePawnsEast = isWhite ? (wPawnsAble2CaptureEast(pawns, oppPawns)) : (bPawnsAble2CaptureEast(pawns, oppPawns));
	uint64_t capturePawnsWest = isWhite ? (wPawnsAble2CaptureWest(pawns, oppPawns)) : (bPawnsAble2CaptureWest(pawns, oppPawns));
	uint64_t captureTargetsEast = isWhite ? (wPawnEastAttacks(capturePawnsEast)) : (bPawnEastAttacks(capturePawnsEast));
	uint64_t captureTargetsWest = isWhite ? (wPawnWestAttacks(capturePawnsWest)) : (bPawnWestAttacks(capturePawnsWest));
	// East
	while (captureTargetsEast != 0) {
		int endSquare = bitScanForward(captureTargetsEast);
		int fromSquare = endSquare + (isWhite ? -9 : 9);
		addMove(fromSquare, endSquare, 0x4, moveList);

		captureTargetsEast &= captureTargetsEast - 1;
	}
	// West
	while (captureTargetsWest != 0) {
		int endSquare = bitScanForward(captureTargetsWest);
		int fromSquare = endSquare + (isWhite ? -7 : 7);
		addMove(fromSquare, endSquare, 0x4, moveList);

		captureTargetsWest &= captureTargetsWest - 1;
	}
}
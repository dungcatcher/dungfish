#include "movegen.hpp"
#include "tables.hpp"
#include "bitutils.hpp"

std::string prettyPrintBitboard(uint64_t bb) {
	std::bitset<64> bitset(bb);
	std::string binaryString = bitset.to_string();
	std::string splitBinaryString = "";
	for (int rank = 0; rank < 8; rank++) {
		for (int file = 7; file >= 0; file--) {
			splitBinaryString += binaryString[rank * 8 + file];
		}
		splitBinaryString += "\n";
	}

	return splitBinaryString;
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


void generatePawnMoves(std::vector<Move> &moveList, const Board& board) {
	uint64_t pawns = board.turn ? board.getWhitePawns() : board.getBlackPawns();
	uint64_t oppPawns = board.turn ? board.getBlackPawns() : board.getWhitePawns();
	uint64_t empty = ~board.getOccupied();

	// Pawn pushes
	uint64_t singlePushPawns = board.turn ? (wPawnsAble2Push(pawns, empty)) : (bPawnsAble2Push(pawns, empty));
	uint64_t singlePushTargets = board.turn ? (wSinglePushTargets(singlePushPawns, empty)) : (bSinglePushTargets(singlePushPawns, empty));
	while (singlePushTargets != 0) { // Loop through 1 bits of target squares
		int endSquare = bitScanForward(singlePushTargets); 
		int fromSquare = endSquare + (board.turn ? -8 : 8); // Trace back to origin square
		addMove(fromSquare, endSquare, 0x0, moveList);

		singlePushTargets &= singlePushTargets - 1; // Set ls1b to 0
	}

	uint64_t dblPushPawns = board.turn ? (wPawnsAble2DblPush(pawns, empty)) : (bPawnsAble2DblPush(pawns, empty));
	uint64_t dblPushTargets = board.turn ? (wDblPushTargets(dblPushPawns, empty)) : (bDblPushTargets(dblPushPawns, empty));
	while (dblPushTargets != 0) {
		int endSquare = bitScanForward(dblPushTargets); 
		int fromSquare = endSquare + (board.turn ? -16 : 16);
		addMove(fromSquare, endSquare, 0x1, moveList);

		dblPushTargets &= dblPushTargets - 1;
	}

	// Captures
	uint64_t capturePawnsEast = board.turn ? (wPawnsAble2CaptureEast(pawns, oppPawns)) : (bPawnsAble2CaptureEast(pawns, oppPawns));
	uint64_t capturePawnsWest = board.turn ? (wPawnsAble2CaptureWest(pawns, oppPawns)) : (bPawnsAble2CaptureWest(pawns, oppPawns));
	uint64_t captureTargetsEast = board.turn ? (wPawnEastAttacks(capturePawnsEast)) : (bPawnEastAttacks(capturePawnsEast));
	uint64_t captureTargetsWest = board.turn ? (wPawnWestAttacks(capturePawnsWest)) : (bPawnWestAttacks(capturePawnsWest));
	// East
	while (captureTargetsEast != 0) {
		int endSquare = bitScanForward(captureTargetsEast);
		int fromSquare = endSquare + (board.turn ? -9 : 9);
		addMove(fromSquare, endSquare, 0x4, moveList);

		captureTargetsEast &= captureTargetsEast - 1;
	}
	// West
	while (captureTargetsWest != 0) {
		int endSquare = bitScanForward(captureTargetsWest);
		int fromSquare = endSquare + (board.turn ? -7 : 7);
		addMove(fromSquare, endSquare, 0x4, moveList);

		captureTargetsWest &= captureTargetsWest - 1;
	}
}

void generateKnightMoves(std::vector<Move> &moveList, const Board& board) {
	uint64_t knights = board.turn ? board.getWhiteKnights() : board.getBlackKnights();
	const uint64_t teamPieces = board.turn ? board.getWhite() : board.getBlack();

	while (knights != 0) {
		int fromSquare = bitScanForward(knights);
		uint64_t pseudoKnightAttacks = knightAttacks[fromSquare];
		pseudoKnightAttacks &= ~teamPieces;
		while (pseudoKnightAttacks != 0) {
			int endSquare = bitScanForward(pseudoKnightAttacks);
			addMove(fromSquare, endSquare, 0x0, moveList);
			pseudoKnightAttacks &= pseudoKnightAttacks - 1;
		}
		knights &= knights - 1;
	}
}

// Sliding pieces

uint64_t getPositiveRayAttacks(uint64_t occupied, int square, Direction dir) {
	uint64_t attacks = rays[dir][square];
	uint64_t blockers = attacks & occupied; // All pieces in the way of the ray
	if (blockers) {
		square = bitScanForward(blockers);
		attacks ^= rays[dir][square];
	}
	return attacks;
}

uint64_t getNegativeRayAttacks(uint64_t occupied, int square, Direction dir) {
	uint64_t attacks = rays[dir][square];
	uint64_t blockers = attacks & occupied;
	if (blockers) {
		square = bitScanReverse(blockers);
		attacks ^= rays[dir][square];
	}
	return attacks;
}

uint64_t generateBishopAttacks(uint64_t blockers, int square) {
	uint64_t attacks = 0;
	
	attacks |= getPositiveRayAttacks(blockers, square, NORTH_EAST);
	attacks |= getPositiveRayAttacks(blockers, square, NORTH_WEST);
	attacks |= getNegativeRayAttacks(blockers, square, SOUTH_EAST);
	attacks |= getNegativeRayAttacks(blockers, square, SOUTH_WEST);

	return attacks;
}

uint64_t generateRookAttacks(uint64_t blockers, int square) {
	uint64_t attacks = 0;

	attacks |= getPositiveRayAttacks(blockers, square, NORTH);
	attacks |= getPositiveRayAttacks(blockers, square, EAST);
	attacks |= getPositiveRayAttacks(blockers, square, WEST);
	attacks |= getNegativeRayAttacks(blockers, square, SOUTH);

	return attacks;
}

uint64_t generateQueenAttacks(uint64_t blockers, int square) {
	uint64_t attacks = generateRookAttacks(blockers, square) | generateBishopAttacks(blockers, square);
	
	return attacks;
}

// 🤢🔫
void generateBishopMoves(std::vector<Move> &moveList, const Board& board) {
	uint64_t bishops = board.turn ? board.getWhiteBishops() : board.getBlackBishops();
	uint64_t teamPieces = board.turn ? board.getWhite() : board.getBlack();
	uint64_t enemyPieces = board.turn ? board.getBlack() : board.getWhite();
	uint64_t blockers = teamPieces | enemyPieces;

	while (bishops) { // Loop through bishops and generate their attacks
		int fromSquare = bitScanForward(bishops);
		uint64_t bishopAttacks = generateBishopAttacks(blockers, fromSquare);
		while (bishopAttacks) {
			int endSquare = bitScanForward(bishopAttacks);
			uint64_t endSquareBits = (uint64_t)0x1 << endSquare;
			// Check if attacks are on pieces or empty squares
			if (blockers & endSquareBits) {
				if (enemyPieces & endSquareBits)
					addMove(fromSquare, endSquare, 0x4, moveList);
			}
			else
				addMove(fromSquare, endSquare, 0x0, moveList);
			bishopAttacks &= bishopAttacks - 1;
		}
		bishops &= bishops - 1;
	}
}

void generateRookMoves(std::vector<Move> &moveList, const Board& board) {
	uint64_t rooks = board.turn ? board.getWhiteRooks() : board.getBlackRooks();
	uint64_t teamPieces = board.turn ? board.getWhite() : board.getBlack();
	uint64_t enemyPieces = board.turn ? board.getBlack() : board.getWhite();
	uint64_t blockers = teamPieces | enemyPieces;

	while (rooks) {
		int fromSquare = bitScanForward(rooks);
		uint64_t rookAttacks = generateRookAttacks(blockers, fromSquare);
		while (rookAttacks) {
			int endSquare = bitScanForward(rookAttacks);
			uint64_t endSquareBits = (uint64_t)0x1 << endSquare;
			// Check if attacks are on pieces or empty squares
			if (blockers & endSquareBits) {
				if (enemyPieces & endSquareBits)
					addMove(fromSquare, endSquare, 0x4, moveList);
			}
			else
				addMove(fromSquare, endSquare, 0x0, moveList);
			rookAttacks &= rookAttacks - 1;
		}
		rooks &= rooks - 1;
	}
}

void generateQueenMoves(std::vector<Move> &moveList, const Board& board) {
	generateBishopMoves(moveList, board);
	generateRookMoves(moveList, board);
}

void generateKingMoves(std::vector<Move> &moveList, const Board& board) {
	uint64_t king = board.turn ? board.getWhiteKings() : board.getBlackKings();
	uint64_t teamPieces = board.turn ? board.getWhite() : board.getBlack();

	while (king != 0) {
		int fromSquare = bitScanForward(king);
		uint64_t pseudoKingAttacks = kingAttacks[fromSquare];
		pseudoKingAttacks &= ~teamPieces;
		while (pseudoKingAttacks != 0) {
			int endSquare = bitScanForward(pseudoKingAttacks);
			addMove(fromSquare, endSquare, 0x0, moveList);
			pseudoKingAttacks &= pseudoKingAttacks - 1;
		}
		king &= king - 1;
	}
}
#include "board.hpp"
#include "tables.hpp"

#include <iostream> 
#include <bitset>
#include <sstream>

Board::Board(std::string fen) {
    parseFen(fen);
}

uint64_t Board::getPieceSet(enumPiece pt) const {return pieceBitboards[pt];}
uint64_t Board::getOccupied() const {return pieceBitboards[nWhite] | pieceBitboards[nBlack];}
uint64_t Board::getWhite() const {return pieceBitboards[nWhite];}
uint64_t Board::getBlack() const {return pieceBitboards[nBlack];}
uint64_t Board::getWhitePawns() const {return pieceBitboards[nPawn] & pieceBitboards[nWhite];}
uint64_t Board::getBlackPawns() const {return pieceBitboards[nPawn] & pieceBitboards[nBlack];}
uint64_t Board::getWhiteKnights() const {return pieceBitboards[nKnight] & pieceBitboards[nWhite];}
uint64_t Board::getBlackKnights() const {return pieceBitboards[nKnight] & pieceBitboards[nBlack];}
uint64_t Board::getWhiteBishops() const {return pieceBitboards[nBishop] & pieceBitboards[nWhite];}
uint64_t Board::getBlackBishops() const {return pieceBitboards[nBishop] & pieceBitboards[nBlack];}
uint64_t Board::getWhiteRooks() const {return pieceBitboards[nRook] & pieceBitboards[nWhite];}
uint64_t Board::getBlackRooks() const {return pieceBitboards[nRook] & pieceBitboards[nBlack];}
uint64_t Board::getWhiteQueens() const {return pieceBitboards[nQueen] & pieceBitboards[nWhite];}
uint64_t Board::getBlackQueens() const {return pieceBitboards[nQueen] & pieceBitboards[nBlack];}
uint64_t Board::getWhiteKings() const {return pieceBitboards[nKing] & pieceBitboards[nWhite];}
uint64_t Board::getBlackKings() const {return pieceBitboards[nKing] & pieceBitboards[nBlack];}

std::string Board::getPieceAtLocation(int x, int y) const {
    y = 7 - y;  // Reverse y value
    int squareIndex = 8 * y + x;
    uint64_t bitIndex = (uint64_t)1 << squareIndex;
    for (int i = 2; i < 8; i++) {
        if ((pieceBitboards[i] & bitIndex) != 0) {
            std::string pieceLetter = PIECE_LETTERS[i];
            if ((pieceBitboards[nWhite] & bitIndex) != 0) // White is uppercase
                for (auto & c: pieceLetter) c = toupper(c);
            return pieceLetter;
        }
    };
    return "";
};

int Board::getPieceAt(int square) const {
    uint64_t squareBb = (uint64_t)0x1 << square;
    for (int pieceIdx = nPawn; pieceIdx <= nKing; pieceIdx++) {
        if (pieceBitboards[pieceIdx] & squareBb) {
            return pieceIdx;
        }
    }
    return -1;
}

std::string Board::prettyPrint() const {
    std::string s;
    for (int y = 0; y < 8; y++) {
        s += "+---+---+---+---+---+---+---+---+\n";
        for (int x = 0; x < 8; x++) {
            s += "| ";
            if (getPieceAtLocation(x, y) != "")
                s += getPieceAtLocation(x, y) + " ";
            else
                s += "  ";
        }
        s += "|\n";
    }
    s += "+---+---+---+---+---+---+---+---+\n";

    return s;
};

std::string Board::print() const {
    std::string s;
    for (int y = 0; y < 8; y++) {
        for (int x = 0; x < 8; x++) {
            if (getPieceAtLocation(x, y) == "")
                s += ". ";
            else
                s += getPieceAtLocation(x, y) + " ";
        }
        s += "\n";
    }
    s += "\n";

    return s;
};

void Board::parseFen(std::string fen) {
    std::string buffer;
    std::stringstream ss(fen);
    std::vector<std::string> fields;

    while (ss >> buffer) 
        fields.push_back(buffer);
    
    // 1. Position data
    int rank = 0;
    int file = 0;

    for (auto &ch : fields[FEN_POSITION]) {
        int lerfIdx = (8 * (7 - rank)) + (file);
        uint64_t bitboardIdx = (uint64_t)0x1 << lerfIdx;

        if (isalpha(ch)) { // Is a piece
            if (isupper(ch))  // White
                pieceBitboards[nWhite] |= bitboardIdx;
            else // Black
                pieceBitboards[nBlack] |= bitboardIdx;

            // Piece types
            char lowerCh = tolower(ch);
            switch (lowerCh) {
                case 'p':
                    pieceBitboards[nPawn] |= bitboardIdx; break;
                case 'n':
                    pieceBitboards[nKnight] |= bitboardIdx; break;
                case 'b':
                    pieceBitboards[nBishop] |= bitboardIdx; break;
                case 'r':
                    pieceBitboards[nRook] |= bitboardIdx; break;
                case 'q':
                    pieceBitboards[nQueen] |= bitboardIdx; break;
                case 'k':
                    pieceBitboards[nKing] |= bitboardIdx; break;
            }
        }

        if (std::isdigit(ch))
            file += ch - '0'; // Numerical value of digit char
        else 
            file++;
        
        if (ch == '/') {
            file = 0;
            rank++;
        }
    }

    // 2. Active colour
    turn = fields[FEN_TURN] == "w" ? 1 : 0;

    // 3. Castling availability
    if (!(fields[FEN_CASTLING].find("k") != std::string::npos))
        blackCastleK = false;
    if (!(fields[FEN_CASTLING].find("q") != std::string::npos))
        blackCastleQ = false;
    if (!(fields[FEN_CASTLING].find("K") != std::string::npos))
        whiteCastleK = false;
    if (!(fields[FEN_CASTLING].find("Q") != std::string::npos))
        whiteCastleQ = false;

    // 4. En passant target square
    if (fields[FEN_ENPASSANT] != "-")
        enpassantSquare = coordinateIndexMap[fields[FEN_ENPASSANT]];

    // 5. 50-move Halfmove clock
    if (fields.size() - 1 >= FEN_HALFMOVE && fields[FEN_HALFMOVE] != "-")
        fiftyMoveHalfmoves = (unsigned int)std::stoi(fields[FEN_HALFMOVE]);
    
    // 6. Full moves
    if (fields.size() - 1 >= FEN_FULLMOVE && fields[FEN_FULLMOVE] != "-")
        fiftyMoveHalfmoves = (unsigned int)std::stoi(fields[FEN_FULLMOVE]);
};

uint64_t Board::getAttackMap(bool colour) const {
    uint64_t pawns, knights, rooks, bishops, queens, kings, occupied;
    pawns   = colour ? getWhitePawns() : getBlackPawns();
    knights = colour ? getWhiteKnights() : getBlackKnights();
    rooks   = colour ? getWhiteRooks() : getBlackRooks();
    bishops = colour ? getWhiteBishops() : getBlackBishops();
    queens = colour ? getWhiteQueens() : getBlackQueens();
    kings = colour ? getWhiteKings() : getBlackKings();
    occupied = getOccupied();

    uint64_t pawnAttackMap = colour ? wPawnAnyAttacks(pawns) : bPawnAnyAttacks(pawns);
    uint64_t knightAttackMap = 0;
    uint64_t rookAttackMap = 0;
    uint64_t bishopAttackMap = 0;
    uint64_t queenAttackMap = 0;
    uint64_t kingAttackMap = 0;
    while (knights) {
        int knightSquare = bitScanForward(knights);
        knightAttackMap |= knightAttacks[knightSquare];
        knights &= knights - 1;
    }
    while (rooks) {
        int rookSquare = bitScanForward(rooks);
        rookAttackMap |= generateRookAttacks(occupied, rookSquare);
        rooks &= rooks - 1;
    }
    while (bishops) {
        int bishopSquare = bitScanForward(bishops);
        bishopAttackMap |= generateBishopAttacks(occupied, bishopSquare);
        bishops &= bishops - 1;
    }
    while (queens) {
        int queenSquare = bitScanForward(queens);
        queenAttackMap |= generateQueenAttacks(occupied, queenSquare);
        queens &= queens - 1;
    }
    while (kings) {
        int kingSquare = bitScanForward(kings);
        kingAttackMap |= kingAttacks[kingSquare];
        kings &= kings - 1;
    }
    return pawnAttackMap | knightAttackMap | bishopAttackMap | rookAttackMap | queenAttackMap | kingAttackMap;
}

uint64_t Board::getAttacksToKing(bool colour) const {
    uint64_t kingSquareBb = colour ? getWhiteKings() : getBlackKings();
    return getAttackMap(!colour) & kingSquareBb;
}

void Board::makeMove(Move move) {
    uint64_t fromBb = (uint64_t)0x1 << move.start;
    uint64_t endBb = (uint64_t)0x1 << move.end;
    uint64_t fromToBb = fromBb ^ endBb;

    int movePieceType = getPieceAt(move.start);
    int endPieceType = getPieceAt(move.end);

    int turnBbIdx = turn ? nWhite : nBlack;
    int oppTurnBbIdx = turn ? nBlack : nWhite;

    pieceBitboards[turnBbIdx] ^= fromToBb; // Update colour bitboard
    if (move.flags & 0x8) { // Promotions
        unsigned int promotionTypeIndex = (move.flags & 0x3) + 3; // Get promotion type and add 3 to correspond with piece bitboard index
        pieceBitboards[movePieceType] ^= fromBb;
        pieceBitboards[promotionTypeIndex] ^= endBb;
    }
    else
        pieceBitboards[movePieceType] ^= fromToBb; // Move piece to location
    
    if (move.flags == 0x5) { // En passant
        uint64_t epCapturePieceBb = (uint64_t)0x1 << (enpassantSquare + (turn ? -8 : 8));
        pieceBitboards[nPawn] ^= epCapturePieceBb; // Remove enpassant piece
        pieceBitboards[oppTurnBbIdx] ^= epCapturePieceBb;
    }
    else if (move.flags & 0x4) { // Capture 
        pieceBitboards[endPieceType] ^= endBb;
        pieceBitboards[oppTurnBbIdx] ^= endBb;
    }
    
    if (move.flags == 0x1) // Double push
        enpassantSquare = move.end + (turn ? -8 : 8);
    else
        enpassantSquare = -1;

    if (move.flags == 0x2) {
        uint64_t rookMove = eastOne(endBb) | westOne(endBb);
        pieceBitboards[nRook] ^= rookMove;
        pieceBitboards[turnBbIdx] ^= rookMove;
    }
    else if (move.flags == 0x3) {
        uint64_t rookMove = eastOne(endBb) | westOne(westOne(endBb));
        pieceBitboards[nRook] ^= rookMove;
        pieceBitboards[turnBbIdx] ^= rookMove;
    }

    // Update castling rights
    if (movePieceType == nKing)
        if (turn) {
            whiteCastleK = false;
            whiteCastleQ = false;
        }
        else {
            blackCastleK = false;
            blackCastleQ = false;
        }
    else if (movePieceType == nRook) {
        if (turn) {
            if (move.start == 0)
                whiteCastleQ = false;
            else if (move.start == 7)
                whiteCastleK = false;
        }
        else {
            if (move.start == 56)
                blackCastleQ = false;
            else if (move.start == 63)
                blackCastleK = false;
        }
    }

    turn = !turn;
}
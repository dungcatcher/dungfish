#include "board.hpp"
#include <iostream> 
#include <bitset>

Board::Board(std::string fen) {
    parseFen(fen);
}

uint64_t Board::getPieceSet(enumPiece pt) {return pieceBitboards[pt];}
uint64_t Board::getOccupied() {return pieceBitboards[nWhite] | pieceBitboards[nBlack];}
uint64_t Board::getWhite() {return pieceBitboards[nWhite];}
uint64_t Board::getBlack() {return pieceBitboards[nBlack];}
uint64_t Board::getWhitePawns() {return pieceBitboards[nPawn] & pieceBitboards[nWhite];}
uint64_t Board::getBlackPawns() {return pieceBitboards[nPawn] & pieceBitboards[nBlack];}
uint64_t Board::getWhiteKnights() {return pieceBitboards[nKnight] & pieceBitboards[nWhite];}
uint64_t Board::getBlackKnights() {return pieceBitboards[nKnight] & pieceBitboards[nBlack];}
uint64_t Board::getWhiteBishops() {return pieceBitboards[nBishop] & pieceBitboards[nWhite];}
uint64_t Board::getBlackBishops() {return pieceBitboards[nBishop] & pieceBitboards[nBlack];}
uint64_t Board::getWhiteRooks() {return pieceBitboards[nRook] & pieceBitboards[nWhite];}
uint64_t Board::getBlackRooks() {return pieceBitboards[nRook] & pieceBitboards[nBlack];}
uint64_t Board::getWhiteQueens() {return pieceBitboards[nQueen] & pieceBitboards[nWhite];}
uint64_t Board::getBlackQueens() {return pieceBitboards[nQueen] & pieceBitboards[nBlack];}

std::string Board::getPieceAtLocation(int x, int y) {
    y = 7 - y;  // Reverse y value
    int squareIndex = 8 * y + x;
    uint64_t bitIndex = (uint64_t)1 << squareIndex;
    for (int i = 2; i < 8; i++) {
        if ((pieceBitboards[i] & bitIndex) != 0) {
            std::string pieceLetter = pieceLetters[i];
            if ((pieceBitboards[nWhite] & bitIndex) != 0) // White is uppercase
                for (auto & c: pieceLetter) c = toupper(c);
            return pieceLetter;
        }
    };
    return "";
};

std::string Board::prettyPrint() {
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

void Board::parseFen(std::string fen) {
    int rank = 0;
    int file = 0;

    for (auto &ch : fen) {
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
}
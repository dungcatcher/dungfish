#pragma once

#include <cstdint>
#include <string>

class Board {   
public:
    uint64_t pieceBitboards[8] = {};
    enum enumPiece {
        nWhite, nBlack, nPawn, nKnight, nBishop, nRook, nQueen, nKing
    };
    uint64_t getPieceSet(enumPiece pt);
    uint64_t getWhite();
    uint64_t getBlack();
    uint64_t getOccupied(); // All occupied squares
    uint64_t getWhitePawns();
    uint64_t getBlackPawns();
    uint64_t getWhiteKnights();
    uint64_t getBlackKnights();
    uint64_t getWhiteBishops();
    uint64_t getBlackBishops();
    uint64_t getWhiteRooks();
    uint64_t getBlackRooks();
    uint64_t getWhiteQueens();
    uint64_t getBlackQueens();
    uint64_t getWhiteKings();
    uint64_t getBlackKings();
    
    std::string getPieceAtLocation(int x, int y);
    std::string prettyPrint();

    void parseFen(std::string fen);
    Board(std::string fen);

    std::string pieceLetters[8] = { "w", "b", "p", "n", "b", "r", "q", "k" };
};
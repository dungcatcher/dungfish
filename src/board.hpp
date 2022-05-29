#pragma once

#include <cstdint>
#include <string>

class Board {   
public:
    uint64_t pieceBitboards[8] = {};
    enum enumPiece {
        nWhite, nBlack, nPawn, nKnight, nBishop, nRook, nQueen, nKing
    };
    uint64_t getPieceSet(enumPiece pt) const;
    uint64_t getWhite() const;
    uint64_t getBlack() const;
    uint64_t getOccupied() const; // All occupied squares
    uint64_t getWhitePawns() const;
    uint64_t getBlackPawns() const;
    uint64_t getWhiteKnights() const;
    uint64_t getBlackKnights() const;
    uint64_t getWhiteBishops() const;
    uint64_t getBlackBishops() const;
    uint64_t getWhiteRooks() const;
    uint64_t getBlackRooks() const;
    uint64_t getWhiteQueens() const;
    uint64_t getBlackQueens() const;
    uint64_t getWhiteKings() const;
    uint64_t getBlackKings() const;
    
    std::string getPieceAtLocation(int x, int y);
    std::string prettyPrint();

    void parseFen(std::string fen);
    Board(std::string fen);

    bool turn = 1; // 1 - white, 0 - black

    std::string pieceLetters[8] = { "w", "b", "p", "n", "b", "r", "q", "k" };
};
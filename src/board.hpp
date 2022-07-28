#pragma once

#include <cstdint>
#include <string>

#include "movegen.hpp"

inline std::string PIECE_LETTERS[8] = { "w", "b", "p", "n", "b", "r", "q", "k" };

class Move; // Forward declaration

class Board {   
public:
    uint64_t pieceBitboards[8] = {};
    enum enumPiece {
        nWhite, nBlack, nPawn, nKnight, nBishop, nRook, nQueen, nKing
    };

    Board(std::string fen); // Coonstructor

    // Getters
    uint64_t getPieceSet(enumPiece pt) const;   
    uint64_t getWhite()        const;
    uint64_t getBlack()        const;
    uint64_t getOccupied()     const; // All occupied squares
    uint64_t getWhitePawns()   const;
    uint64_t getBlackPawns()   const;
    uint64_t getWhiteKnights() const;
    uint64_t getBlackKnights() const;
    uint64_t getWhiteBishops() const;
    uint64_t getBlackBishops() const;
    uint64_t getWhiteRooks()   const;
    uint64_t getBlackRooks()   const;
    uint64_t getWhiteQueens()  const;
    uint64_t getBlackQueens()  const;
    uint64_t getWhiteKings()   const;
    uint64_t getBlackKings()   const;

    int getPieceAt(int square) const;
    
    std::string getPieceAtLocation(int x, int y);
    std::string prettyPrint();
    std::string print();

    void parseFen(std::string fen);    

    void makeMove(Move move);
    void unmakeMove(Move move);

    uint64_t getAttackMap(bool colour) const;
    uint64_t getAttacksToKing(bool colour) const;

    bool turn = 1; // 1 - white, 0 - black

    // Castling rights (ie king hasnt moved)
    bool whiteCastleK = true;
    bool whiteCastleQ = true;
    bool blackCastleK = true;
    bool blackCastleQ = true;

    int enpassantSquare = -1; // Square that can be taken enpassant
};
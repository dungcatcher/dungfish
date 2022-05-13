#include <cstdint>
#include <string>

class Board {   
    uint64_t pieceBitboards[8] = {
        0x000000000000FFFF, // White
        0xFFFF000000000000, // Black
        0x00FF00000000FF00, // Pawn
        0x4200000000000042, // Knight
        0x2400000000000024, // Bishop
        0x8100000000000081, // Rook
        0x1000000000000010, // Queen
        0x0800000000000008 // King
    };
public:
    std::string getPieceAtLocation(int x, int y);
    std::string prettyPrint();
    enum enumPiece {
        nWhite, nBlack, nPawn, nKnight, nBishop, nRook, nQueen, nKing
    };
    std::string pieceLetters[8] = { "w", "b", "p", "n", "b", "r", "q", "k" };
};
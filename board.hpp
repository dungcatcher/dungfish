#include <cstdint>
#include <string>

class Board {   
    uint64_t pieceBitboard[8] = {
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
    std::string prettyPrint();
    enum enumPiece {
        nWhite, // Any white piece
        nBlack, // Any black piecce
        nPawn, // Any pawn etc.
        nKnight,
        nBishop,
        nRook,
        nQueen,
        nKing
    };
};
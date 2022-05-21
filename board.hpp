#include <cstdint>
#include <string>

class Board {   
public:
    uint64_t pieceBitboards[8] = {};
    enum enumPiece {
        nWhite, nBlack, nPawn, nKnight, nBishop, nRook, nQueen, nKing
    };
    uint64_t getPieceSet(enumPiece pt);
    uint64_t getOccupied(); // All occupied squares
    uint64_t getWhitePawns();
    uint64_t getBlackPawns();
    
    std::string getPieceAtLocation(int x, int y);
    std::string prettyPrint();

    void parseFen(std::string fen);
    Board(std::string fen);

    std::string pieceLetters[8] = { "w", "b", "p", "n", "b", "r", "q", "k" };
};
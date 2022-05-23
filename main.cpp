#include <iostream>
#include <string>
#include <vector>

#include "board.hpp"
#include "movegen.hpp"
#include "tables.hpp"

int main()
{
    std::string startFen = "rnbqkbnr/pppppppp/8/8/8/pppp4/PPPPPPPP/RNBQKBNR";
    Board board(startFen);
    std::cout << board.prettyPrint();

    initTables();

    std::vector<Move> moveList;
    generatePawnMoves(moveList, true, board.getWhitePawns(), board.getBlackPawns(), ~board.getOccupied());
    generateKnightMoves(moveList, board.getWhiteKnights(), board.getPieceSet(Board::enumPiece::nWhite));

    for (auto &move : moveList) {
        std::cout << move.start << " to " << move.end << " flags: " << move.flags << "\n";
    }

    return 0;
}
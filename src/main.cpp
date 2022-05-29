#include <iostream>
#include <string>
#include <vector>

#include "board.hpp"
#include "movegen.hpp"
#include "tables.hpp"
#include "rays.hpp"

int main()
{
    std::string startFen = "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR";
    Board board(startFen);
    initRays();
    std::cout << board.prettyPrint();

    initTables();

    std::vector<Move> moveList;
    generatePawnMoves(moveList, board);
    generateKnightMoves(moveList, board);
    generateBishopMoves(moveList, board);
    generateRookMoves(moveList, board);
    generateQueenMoves(moveList, board);
    generateKingMoves(moveList, board);

    for (auto &move : moveList) {
        std::string start = coordinateIndexTable[move.start];
        std::string end = coordinateIndexTable[move.end];
        std::cout << start << " to " << end << " flags: " << move.flags << "\n";
    }

    return 0;
}
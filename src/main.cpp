#include <iostream>
#include <string>
#include <vector>

#include "board.hpp"
#include "movegen.hpp"
#include "tables.hpp"
#include "rays.hpp"

int main()
{
    std::string startFen = "rnbqkbnr/PPPPPPPP/8/8/8/8/PPPPPPPP/RNBQK3";
    Board board(startFen);
    board.turn = 1;
    initRays();

    std::cout << board.prettyPrint();

    initTables();

    std::vector<Move> moveList;
    moveList.reserve(256);

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
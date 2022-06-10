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
    initTables();

    std::vector<Move> moveList;
    moveList.reserve(256);

    generateLegalMoves(moveList, board);
    for (auto &move : moveList) {
        Board newBoard = board;
        newBoard.makeMove(move);
        std::cout << newBoard.print() << "\n";
    }

    return 0;
}
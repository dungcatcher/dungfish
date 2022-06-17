#include <iostream>
#include <string>
#include <vector>

#include "board.hpp"
#include "movegen.hpp"
#include "tables.hpp"
#include "rays.hpp"

int main()
{
    std::string startFen = "rnbqkbnr/pppppppp/8/8/rrrrrrrr/8/8/RNBQKBNR";
    Board board(startFen);

    initRays();
    initTables();

    std::vector<Move> moveList;
    moveList.reserve(256);

    std::vector<Move> legalMoveList = generateLegalMoves(moveList, board);
    for (auto &move : legalMoveList) {
        Board newBoard = board;
        newBoard.makeMove(move);
        std::cout << newBoard.print() << "\n";
    }

    std::cout << perft(4, board);

    return 0;
}
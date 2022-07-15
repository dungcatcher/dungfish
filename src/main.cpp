#include <iostream>
#include <string>
#include <vector>
#include <chrono>

#include "board.hpp"
#include "movegen.hpp"
#include "tables.hpp"
#include "rays.hpp"

int main()
{
    std::string startFen = "r1bqkbnr/pppppppp/8/8/1n6/P7/2PPPPPP/RNBQKBNR";
    Board board(startFen);
    board.turn = 1;

    initRays();
    initTables();

    std::vector<Move> moveList;
    moveList = generateLegalMoves(moveList, board);
    for (auto &move : moveList) {
        Board newBoard = board;
        newBoard.makeMove(move);
        std::cout << coordinateIndexTable[move.start] << coordinateIndexTable[move.end] << ": " << perft(0, newBoard) << "\n";
    }
    
    auto start = std::chrono::steady_clock::now();
    int perftNum = perft(1, board);
    std::cout << perftNum << "\n";
    auto end = std::chrono::steady_clock::now();

    auto elapsedTime = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
    double nps = (double)perftNum / ((double)elapsedTime / 1000.0);
    std::cout << "Nodes per second: " << nps << "\n";

    return 0;
}
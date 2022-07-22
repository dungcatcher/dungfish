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
    std::string startFen = "r3k2r/p1ppqpb1/bn2pnp1/3PN3/1p2P3/2N2Q1p/PPPBBPPP/R3K2R";
    Board board(startFen);

    board.turn = 1;

    initRays();
    initTables();

    std::vector<Move> moveList;
    moveList = generateLegalMoves(moveList, board);
    for (auto &move : moveList) {
        Board newBoard = board;
        newBoard.makeMove(move);
        std::cout << coordinateIndexTable[move.start] << coordinateIndexTable[move.end] << ": " << perft(1, newBoard) << "\n";
    }
    
    auto start = std::chrono::steady_clock::now();
    int perftNum = perft(2, board);
    std::cout << perftNum << "\n";
    auto end = std::chrono::steady_clock::now();

    auto elapsedTime = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
    double nps = (double)perftNum / ((double)elapsedTime / 1000.0);
    std::cout << "Nodes per second: " << nps << "\n";

    return 0;
}
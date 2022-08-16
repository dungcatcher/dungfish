#include <iostream>
#include <string>
#include <vector>
#include <chrono>

#include "board.hpp"
#include "movegen.hpp"
#include "tables.hpp"
#include "rays.hpp"
#include "eval.hpp"
#include "search.hpp"

int main()
{
    std::cout << "Initialising dungfish...\n";

    std::string startFen = "rnbqkbnr/2pppNpp/1p6/p7/8/8/PPPPPPPP/RNBQKB1R w KQkq - 0 4";
    Board board(startFen);

    initRays();
    initTables();
    std::cout << "L done\n";

    int eval = negaMax(board, NEGATIVE_INF, POSITIVE_INF, 4);
    std::cout << "eval: " << eval << "\n";
    
    // auto start = std::chrono::steady_clock::now();
    // int perftNum = perft(5, board, true);
    // std::cout << perftNum << "\n";
    // auto end = std::chrono::steady_clock::now();

    // auto elapsedTime = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
    // double nps = (double)perftNum / ((double)elapsedTime / 1000.0);
    // std::cout << "Nodes per second: " << nps << "\n";

    return 0;
}
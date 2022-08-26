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

    std::string startFen = "r1bqkb1r/pppp1pp1/2n2n1p/4p1N1/2B1P3/8/PPPP1PPP/RNBQK2R w KQkq - 0 5";
    Board board(startFen);

    initRays();
    initTables();
    std::cout << "L done\n";

    int eval = alphaBetaMax(board, NEGATIVE_INF, POSITIVE_INF, 3);
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
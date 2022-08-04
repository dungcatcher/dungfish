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
    std::string startFen = "rnb1kbnr/pppppppp/8/3N4/8/8/PPPPPPPP/R1B1KBNR w KQkq - 0 1";
    Board board(startFen);

    initRays();
    initTables();

    int eval = alphaBetaMax(board, NEGATIVE_INF, POSITIVE_INF, 4);
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
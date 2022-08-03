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
    std::string startFen = "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1";
    Board board(startFen);
    
    int eval = alphaBetaMax(board, NEGATIVE_INF, POSITIVE_INF, 0);
    std::cout << "eval: " << eval << "\n";

    initRays();
    initTables();
    
    auto start = std::chrono::steady_clock::now();
    int perftNum = perft(5, board, true);
    std::cout << perftNum << "\n";
    auto end = std::chrono::steady_clock::now();

    auto elapsedTime = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
    double nps = (double)perftNum / ((double)elapsedTime / 1000.0);
    std::cout << "Nodes per second: " << nps << "\n";

    return 0;
}
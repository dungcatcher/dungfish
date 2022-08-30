#include "board.hpp"
#include <limits>

const int NEGATIVE_INF = std::numeric_limits<int>::min() + 1; // -2147483647
const int POSITIVE_INF = std::numeric_limits<int>::max();     //  2147483647

int negaMax(const Board& board, int alpha, int beta, int depth);

int quiesce(const Board& board, int alpha, int beta);
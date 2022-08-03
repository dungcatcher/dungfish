#include "board.hpp"
#include <limits>

const int NEGATIVE_INF = std::numeric_limits<int>::max();
const int POSITIVE_INF = std::numeric_limits<int>::min();

int alphaBetaMax(const Board& board, int alpha, int beta, int depth);
int alphaBetaMin(const Board& board, int alpha, int beta, int depth);
#include "board.hpp"
#include <limits>

const int NEGATIVE_INF = std::numeric_limits<int>::min();
const int POSITIVE_INF = std::numeric_limits<int>::max();

int alphaBetaMax(const Board& board, int alpha, int beta, int depth);
int alphaBetaMin(const Board& board, int alpha, int beta, int depth);
int quiesce(const Board& board, int alpha, int beta);
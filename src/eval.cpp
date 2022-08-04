#include "eval.hpp"

int evaluate(const Board& board, bool turn) {
    int score = 0;

    score += PAWN_VALUE * (__builtin_popcountll(board.getWhitePawns()) - __builtin_popcountll(board.getBlackPawns()));
    score += KNIGHT_VALUE * (__builtin_popcountll(board.getWhiteKnights()) - __builtin_popcountll(board.getBlackKnights()));
    score += BISHOP_VALUE * (__builtin_popcountll(board.getWhiteBishops()) - __builtin_popcountll(board.getBlackBishops()));
    score += ROOK_VALUE * (__builtin_popcountll(board.getWhiteRooks()) - __builtin_popcountll(board.getBlackRooks()));
    score += QUEEN_VALUE * (__builtin_popcountll(board.getWhiteQueens()) - __builtin_popcountll(board.getBlackQueens()));

    return score;
}
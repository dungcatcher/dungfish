#include "search.hpp"
#include "eval.hpp"
#include "movegen.hpp"

int alphaBetaMax(const Board& board, int alpha, int beta, int depth) {
    if (depth == 0)
        return evaluate(board, board.turn);
    
    std::vector<Move> moveList;
	std::vector<Move> legalMoveList = generateLegalMoves(moveList, board);
    for (auto &move : legalMoveList) {
        int score = alphaBetaMin(board, alpha, beta, depth - 1);
        if (score >= beta) 
            return beta;
        if (score > alpha)
            alpha = score;
    }
    return alpha;
}

int alphaBetaMin(const Board& board, int alpha, int beta, int depth) {
    if (depth == 0)
        return -evaluate(board, board.turn);
    
    std::vector<Move> moveList;
	std::vector<Move> legalMoveList = generateLegalMoves(moveList, board);
    for (auto &move : legalMoveList) {
        int score = alphaBetaMax(board, alpha, beta, depth - 1);
        if (score <= alpha) 
            return alpha;
        if (score < beta)
            beta = score;
    }
    return beta;
}
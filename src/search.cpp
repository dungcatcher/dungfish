#include "search.hpp"
#include "eval.hpp"
#include "movegen.hpp"

int alphaBetaMax(const Board& board, int alpha, int beta, int depth) {
    if (depth == 0)
        return quiesce(board, alpha, beta);
    
    std::vector<Move> moveList;
	std::vector<Move> legalMoveList = generateLegalMoves(moveList, board);
    for (auto &move : legalMoveList) {
        Board newBoard = board;
        newBoard.makeMove(move);

        int score = alphaBetaMin(newBoard, alpha, beta, depth - 1);
        if (score >= beta) 
            return beta;
        if (score > alpha)
            alpha = score;
    }
    return alpha;
}

int alphaBetaMin(const Board& board, int alpha, int beta, int depth) {
    if (depth == 0)
        return -quiesce(board, alpha, beta);
    
    std::vector<Move> moveList;
	std::vector<Move> legalMoveList = generateLegalMoves(moveList, board);
    for (auto &move : legalMoveList) {
        Board newBoard = board;
        newBoard.makeMove(move);

        int score = alphaBetaMax(newBoard, alpha, beta, depth - 1);
        if (score <= alpha) 
            return alpha;
        if (score < beta)
            beta = score;
    }
    return beta;
}

int quiesce(const Board& board, int alpha, int beta) {
    int standPat = evaluate(board, board.turn);
    if (standPat >= beta)
        return beta;
    if (alpha < standPat)
        alpha = standPat;

    std::vector<Move> captureList;
    std::vector<Move> moveList;
    std::vector<Move> legalMoveList = generateLegalMoves(moveList, board);
    for (auto &move : legalMoveList) {
        if (move.flags & 0x4) {
            captureList.push_back(move);
        }
    }

    for (auto &capture : captureList) {
        Board newBoard = board;
        newBoard.makeMove(capture);

        int score = -quiesce(newBoard, -beta, -alpha);

        if (score >= beta)
            return beta;
        if (score > alpha) 
            alpha = score;
    }
    return alpha;
}
#include "search.hpp"
#include "eval.hpp"
#include "movegen.hpp"

int negaMax(const Board& board, int alpha, int beta, int depth) {
    if (depth == 0) {   
        return (board.turn ? 1 : -1) * evaluate(board, board.turn);
    }
        
    std::vector<Move> legalMoveList;
    legalMoveList = generateLegalMoves(legalMoveList, board);

    int value = NEGATIVE_INF;
    for (auto &move : legalMoveList) {
        Board newBoard = board;
        newBoard.makeMove(move);

        value = std::max(value, -negaMax(newBoard, -beta, -alpha, depth - 1));
        alpha = std::max(alpha, value);
        if (alpha >= beta) 
            break;
    }
    return value;
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
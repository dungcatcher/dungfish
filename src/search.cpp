#include "search.hpp"
#include "eval.hpp"
#include "movegen.hpp"

int negaMax(const Board& board, int alpha, int beta, int depth) {
    if (depth == 0) {   
        return (board.turn ? 1 : -1) * evaluate(board, board.turn);
    }
        
    std::vector<Move> legalMoveList;
    legalMoveList = generateLegalMoves(legalMoveList, board);

    for (auto &move : legalMoveList) {
        Board newBoard = board;
        newBoard.makeMove(move);

        int score = -negaMax(newBoard, -beta, -alpha, depth - 1);   
        if (score >= beta)
            return score;
        if (score > alpha) 
            alpha = score;
    }
    return alpha;
}

int quiesce(const Board& board, int alpha, int beta) {
    int standPat = evaluate(board, board.turn);
    if (standPat >= beta)
        return beta;
    if (alpha < standPat)
        alpha = standPat;

    std::vector<Move> legalMoveList;
    legalMoveList = generateLegalMoves(legalMoveList, board);

    for (auto &move : legalMoveList) {
        std::cout << getMoveString(move) << "\n";
        if (move.flags & 0x4) {
            Board newBoard = board;
            newBoard.makeMove(move);

            int score = -quiesce(newBoard, -beta, -alpha);

            if (score >= beta)
                return beta;
            if (score > alpha) 
                alpha = score;
        }
    }
    return alpha;
}
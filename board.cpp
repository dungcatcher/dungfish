#include "board.hpp"
#include <iostream> 
#include <bitset>

std::string Board::getPieceAtLocation(int x, int y) {
    y = 7 - y;  // Reverse y value
    int squareIndex = 8 * y + x;
    uint64_t bitIndex = (uint64_t)1 << squareIndex;
    for (int i = 2; i < 8; i++) {
        if ((pieceBitboards[i] & bitIndex) != 0) {
            std::string pieceLetter = pieceLetters[i];
            if ((pieceBitboards[nWhite] & bitIndex) != 0) // White is uppercase
                for (auto & c: pieceLetter) c = toupper(c);
            return pieceLetter;
        }
    };
    return "";
};

std::string Board::prettyPrint() {
    std::string s;
    for (int y = 0; y < 8; y++) {
        s += "+---+---+---+---+---+---+---+---+\n";
        for (int x = 0; x < 8; x++) {
            s += "| ";
            if (getPieceAtLocation(x, y) != "")
                s += getPieceAtLocation(x, y) + " ";
            else
                s += "  ";
        }
        s += "|\n";
    }
    s += "+---+---+---+---+---+---+---+---+\n";

    return s;
};
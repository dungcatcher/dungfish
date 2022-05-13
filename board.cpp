#include "board.hpp"
#include <iostream> 

std::string Board::prettyPrint() {
    std::string s;
    for (int y = 0; y < 8; y++) {
        s += "+---+---+---+---+---+---+---+---+\n";
        for (int x = 0; x < 8; x++) {
            s += "|   ";
        }
        s += "|\n";
    }
    s += "+---+---+---+---+---+---+---+---+\n";

    return s;
};
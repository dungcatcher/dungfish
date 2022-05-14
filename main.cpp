#include <iostream>
#include <string>
#include "board.cpp"
#include "movegen.cpp"

int main()
{
    Board board;
    std::cout << board.prettyPrint();
    uint64_t e = wPawnsAble2DblPush(board.getWhitePawns(), ~board.getOccupied());
    uint64_t f = wDblPushTargets(e, ~board.getOccupied());
    std::bitset<64> x(f);
    std::cout << x << "\n";
    return 0;
}
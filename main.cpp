#include <iostream>
#include <string>
#include "board.cpp"

int main()
{
    Board board;
    std::string e = board.prettyPrint();
    std::cout << e;

    return 0;
}
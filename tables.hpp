#include <cstdint>

class Table {
public:
    uint64_t knightAttacks[64];
    Table();
    void initKnightAttacks();
};
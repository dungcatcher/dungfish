#include <cstdint>

class Move {
public:
    Move(unsigned int start, unsigned int end, unsigned int flags);
    
};

const uint64_t notAFile = 0xfefefefefefefefe; // ~0x0101010101010101
const uint64_t notHFile = 0x7f7f7f7f7f7f7f7f; // ~0x8080808080808080

uint64_t soutOne (uint64_t b);
uint64_t nortOne (uint64_t b);
uint64_t eastOne (uint64_t b);
uint64_t noEaOne (uint64_t b);
uint64_t soEaOne (uint64_t b);
uint64_t westOne (uint64_t b);
uint64_t soWeOne (uint64_t b);
uint64_t noWeOne (uint64_t b);

uint64_t wSinglePushTargets(uint64_t wpawns, uint64_t empty);
uint64_t wDblPushTargets(uint64_t wpawns, uint64_t empty);
uint64_t bSinglePushTargets(uint64_t bpawns, uint64_t empty);
uint64_t bDoublePushTargets(uint64_t bpawns, uint64_t empty);
uint64_t wPawnsAble2Push(uint64_t wpawns, uint64_t empty);
uint64_t wPawnsAble2DblPush(uint64_t wpawns, uint64_t empty);
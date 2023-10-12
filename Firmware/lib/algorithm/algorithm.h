/**
 * @file algorithm.h
 * @author Joe S
 * @brief Prototypes for the micromouse algorithm
 */

#include <cstdint> // This include might have to be moved..

class Algorithm
{
private:
    /** Every square has 16 bits of possible information
     * 0000 0000 00000000
     * │    │    └─────── Square ID
     * │    └──────────── Unused
     * └───────────────── NSEW walls
     */
    uint16_t maze[16][16];

public:
    // Algorithm(/* args */);

    void init();

    uint16_t getRaw(int x, int y);
};

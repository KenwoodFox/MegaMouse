/**
 * @file data.h
 * @brief Misc data and enum types.
 *
 */

/**
 * @brief All the cardinal directions
 *
 */
enum Cardinal
{
    NORTH = 0b1000000000000000,
    SOUTH = 0b0100000000000000,
    EAST = 0b0010000000000000,
    WEST = 0b0001000000000000,
};

enum Relative
{
    FORWARD,     // Cardinal Forward
    LEFT,        // Cardinal left
    RIGHT,       // Cardinal right
    BACK,        // Cardinal back
    TURN_LEFT,   // Special shortcut for a quick left turn
    TURN_RIGHT,  // Special shortcut for a quick right turn
    TURN_AROUND, // Special shortcut for a quick turnaround
};
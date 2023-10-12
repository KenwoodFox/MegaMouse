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
    LEFT,
    RIGHT,
    BACK,
    FORWARD,
};
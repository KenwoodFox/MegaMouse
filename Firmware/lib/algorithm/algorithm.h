/**
 * @file algorithm.h
 * @author Joe S
 * @brief Prototypes for the micromouse algorithm
 */

#ifndef ARDUINO
#include <cstdint> // This include might have to be moved..
#else
#include <Arduino.h>
#endif

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

/**
 * @brief Data format used by the algorithm to store data about tiles
 *
 */
struct mazeTile
{
    uint8_t walls; // What walls are blocked for this tile
    uint8_t value; // The game value of this tile
};

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
    // Public Data
    // Very important current pose (x and y are map cells)
    uint8_t mapPoseX = 0;
    uint8_t mapPoseY = 0;

    Cardinal mapDir = NORTH; // What does this mean exactly?

    // Algorithm(/* args */);

    void init();

    /**
     * @brief Get the raw maze data for a specific cell
     *
     * @param x
     * @param y
     * @return uint16_t (maze data unit)
     */
    uint16_t getRaw(int x, int y);

    /** Motion Commands
     *
     * Motion commands are not like robot commands, these
     * should be called from odometry, and only used to update the
     * current pose on the map so we do not become lost even
     * during a crash.
     */

    /**
     * @brief Turn one Cardinal direction left
     *
     */
    void turnLeft();

    /**
     * @brief Turn one Cardinal direction left
     *
     */
    void turnRight();

    /**
     * @brief Move one cardinal direction forward
     *
     */
    void forward();

    /**
     * @brief Set wall in cardinal direction
     *
     */
    void setWall(Cardinal dir);

    // Need a point of interest function.
};

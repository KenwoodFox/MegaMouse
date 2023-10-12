/**
 * @file algorithm.h
 * @author Joe S
 * @brief Prototypes for the micromouse algorithm
 */

#ifndef ARDUINO
#include <cstdint>
#include <cmath>
#else
#include <Arduino.h>
#endif

#include "data.h"

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
     * @brief Find the direction from any two locations in the maze.
     *
     * @param startX Where you are (x)
     * @param startY Where you are (y)
     * @param endX   Where you want to be (x)
     * @param endY   Where you want to be (y)
     * @return Cardinal A direction
     */
    Cardinal getDirection(int startX, int startY, int endX, int endY);

    /**
     * @brief Get the raw maze data for a specific cell
     *
     * @param x X coordinate in maze (0-15)
     * @param y Y coordinate in maze (0-15)
     * @return uint16_t (maze data unit)
     */
    uint16_t getRaw(int x, int y);

    /**
     * @brief Get the value of a specific tile
     *
     * @param x X coordinate in maze (0-15)
     * @param y Y coordinate in maze (0-15)
     * @return uint8_t tile value (unsigned int 8 bits)
     */
    uint8_t getValue(int x, int y);

    /**
     * @brief Set the value of a specific tile
     *
     * @param x X coordinate in maze (0-15)
     * @param y Y coordinate in maze (0-15)
     * @param value An 8 bit number (0-255)
     */
    void setValue(int x, int y, uint8_t value);

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

    /**
     * @brief Mark a wall using relative chords
     *
     */
    void markWall(Relative dir);

    // Need a point of interest function.
};

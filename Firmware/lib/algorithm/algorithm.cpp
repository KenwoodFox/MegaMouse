#include "algorithm.h"

// Algorithm::Algorithm()
// {
//     ;
// }

void Algorithm::init()
{
    // maze[4][6] = 0b1111000000000000;
    // maze[4][7] = maze[4][9] | EAST;
}

uint16_t Algorithm::getRaw(int x, int y)
{
    if (x > 16 or y > 16)
    {
        return 0;
    }

    return maze[x][y];
}

uint8_t Algorithm::getValue(int x, int y)
{
    // And with 1111 1111 and get only the last 8 bits
    return maze[x][y] & 0xff;
}

void Algorithm::setValue(int x, int y, uint8_t value)
{
    uint16_t _raw = maze[x][y];
    _raw &= ~0xff; // Clear lower 16
    _raw |= value; // Set lower 16

    maze[x][y] = _raw;
}

void Algorithm::turnLeft()
{
    // This implementation is messy but, then again, so are enums in cpp
    // This could potentially be improved with some enum/array mapping.
    switch (mapDir)
    {
    case NORTH:
        mapDir = WEST;
        break;

    case WEST:
        mapDir = SOUTH;
        break;

    case SOUTH:
        mapDir = EAST;
        break;

    case EAST:
        mapDir = NORTH;
        break;

    default:
        mapDir = NORTH; // How did we get here?...
        break;
    }
}

void Algorithm::turnRight()
{
    switch (mapDir)
    {
    case NORTH:
        mapDir = EAST;
        break;

    case EAST:
        mapDir = SOUTH;
        break;

    case SOUTH:
        mapDir = WEST;
        break;

    case WEST:
        mapDir = NORTH;
        break;

    default:
        mapDir = NORTH; // How did we get here?...
        break;
    }
}

void Algorithm::forward()
{
    // TODO: add map edge detection

    uint8_t _prev = getValue(mapPoseX, mapPoseY);

    switch (mapDir)
    {
    case NORTH:
        mapPoseY += 1;
        break;

    case EAST:
        mapPoseX += 1;
        break;

    case SOUTH:
        mapPoseY -= 1;
        break;

    case WEST:
        mapPoseX -= 1;
        break;
    }

    setValue(mapPoseX, mapPoseY, _prev + 1);
}

void Algorithm::setWall(Cardinal dir)
{
    maze[mapPoseX][mapPoseY] = maze[mapPoseX][mapPoseY] | dir;
}

void Algorithm::markWall(Relative dir)
{
    // Mark relative wall
    ;
}

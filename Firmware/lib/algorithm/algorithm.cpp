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
}

void Algorithm::setWall(Cardinal dir)
{
    maze[mapPoseX][mapPoseY] = maze[mapPoseX][mapPoseY] | dir;
}

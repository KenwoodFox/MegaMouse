#include "algorithm.h"

// Algorithm::Algorithm()
// {
//     ;
// }

void Algorithm::init()
{
    // These first two walls are always known
    setAbsWall(WEST, 0, 0);
    setAbsWall(SOUTH, 0, 0);

    // maze[4][6] = 0b1111000000000000;
    // maze[4][7] = maze[4][9] | EAST;

    // This should be automatic but, this is kinda the idea we want to target.
    // setValue(0, 0, 16);
    // setValue(1, 0, 15);
    // setValue(2, 0, 14);
    // setValue(3, 0, 13);
    // setValue(4, 0, 12);
    // setValue(5, 0, 11);
    // setValue(6, 0, 10);
    // setValue(7, 0, 9);
    // setValue(8, 0, 8);
    // setValue(8, 1, 7);
    // setValue(8, 2, 6);
    // setValue(8, 3, 5);
    // setValue(8, 4, 4);
    // setValue(8, 5, 3);
    // setValue(8, 6, 2);
    // setValue(8, 7, 1);
    // setValue(8, 8, 0);
    setValue(8, 8, 255); // X marks the spot!
    setValue(7, 8, 255);
    setValue(7, 7, 255);
    setValue(8, 7, 255);
}

// Need a function that can find the direction to any square from any square.

Cardinal Algorithm::getDirection(int startX, int startY, int endX, int endY)
{
    if (abs(endY - startY) > abs(endX - endY))
    {
        if (endY > startY)
        {
            return NORTH;
        }
        else
        {
            return SOUTH;
        }
    }
    else
    {
        if (endX > startX)
        {
            return EAST;
        }
        else
        {
            return WEST;
        }
    }
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

bool Algorithm::getWall(Cardinal dir)
{
    // We're using dir as an AND mask here,
    // if the specific bit is set in maze,
    // it will evaulate to true.
    return maze[mapPoseX][mapPoseY] & dir;
}

void Algorithm::setAbsWall(Cardinal dir, uint8_t _px, uint8_t _py)
{
    maze[_px][_py] = maze[_px][_py] | dir;
}

Cardinal Algorithm::rotate(Relative dir)
{
    // This is a messy implementation.. room to optimize!
    if (dir != FORWARD)
    {
        switch (mapDir)
        {
        case NORTH:
            if (dir == LEFT)
            {
                return WEST;
            }
            else
            {
                return EAST;
            }
            break;

        case SOUTH:
            if (dir == LEFT)
            {
                return EAST;
            }
            else
            {
                return WEST;
            }
            break;

        case EAST:
            if (dir == LEFT)
            {
                return NORTH;
            }
            else
            {
                return SOUTH;
            }
            break;

        case WEST:
            if (dir == LEFT)
            {
                return SOUTH;
            }
            else
            {
                return NORTH;
            }
            break;

        default:
            break;
        }
    }

    return mapDir; // If we're scanning forward, then there is no change.
}

void Algorithm::markWall(Relative dir)
{
    setWall(rotate(dir));
}

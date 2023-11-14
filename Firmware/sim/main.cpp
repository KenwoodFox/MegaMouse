#include <iostream>
#include <string>

#include "API.h"       // MMS Simulator API
#include "algorithm.h" // On-robot algorithm

static Algorithm alg; // Create a local instance of algorithm

void log(const std::string &text)
{
    std::cerr << text << std::endl;
}

char toDir(Cardinal _dir)
{
    // Helper to convert raw dir to string
    if (_dir == NORTH)
    {
        return 'N';
    }
    else if (_dir == SOUTH)
    {
        return 'S';
    }
    else if (_dir == EAST)
    {
        return 'E';
    }
    else if (_dir == WEST)
    {
        return 'W';
    }
    return '?';
}

int main(int argc, char *argv[])
{
    log("Initializing algorithm");
    alg.init();

    // We start at the same location every time
    API::setColor(0, 0, 'G');
    API::setText(0, 0, "Start");

    while (true)
    {
        // Mark all walls in this square!
        if (API::wallLeft())
        {
            alg.markWall(LEFT);
        }

        if (API::wallRight())
        {
            alg.markWall(RIGHT);
        }

        if (API::wallFront())
        {
            alg.markWall(FORWARD);
        }

        // Pick a direction to go
        // if (direction is clear)..
        Cardinal intendedDir = alg.getDirection(alg.mapPoseX, alg.mapPoseY, 8, 8);
        if (!alg.getWall(intendedDir)) // If the wall in the intended dir is clear
        {
            log("Intended dir is clear!");

            if (alg.mapDir == intendedDir)
            {
                API::moveForward();
                alg.forward();
            }
            else if (alg.rotate(LEFT) == intendedDir)
            {
                API::turnLeft();
                alg.turnLeft();
                API::moveForward();
                alg.forward();
            }
            else if (alg.rotate(RIGHT) == intendedDir)
            {
                API::turnRight();
                alg.turnRight();
                API::moveForward();
                alg.forward();
            }
        }
        else
        {
            API::turnRight();
            alg.turnRight();
            API::moveForward();
            alg.forward();
        }

        // if (!API::wallLeft())
        // {
        //     alg.setWall(alg.mapDir);
        //     alg.turnLeft();
        //     API::turnLeft();
        // }
        // while (API::wallFront())
        // {
        //     alg.setWall(alg.mapDir);
        //     alg.turnRight();
        //     API::turnRight();
        // }
        // API::moveForward();
        // alg.forward();

        char _buf[20];
        sprintf(_buf, "Intended dir: %c", toDir(alg.getDirection(alg.mapPoseX, alg.mapPoseY, 8, 8)));
        log(_buf);

        // Update the simulator with what the robot has in memory
        for (uint8_t x = 0; x < 16; x++)
        {
            for (uint8_t y = 0; y < 16; y++)
            {
                uint16_t _raw = alg.getRaw(x, y);

                API::setColor(x, y, 'k');

                // Process all cardinals (TODO: clean this up!)
                if (_raw & (1 << 15))
                {
                    API::setWall(x, y, 'n');
                }

                if (_raw & (1 << 14))
                {
                    API::setWall(x, y, 's');
                }

                if (_raw & (1 << 13))
                {
                    API::setWall(x, y, 'e');
                }

                if (_raw & (1 << 12))
                {
                    API::setWall(x, y, 'w');
                }

                // Process spanning numbers
                char _val[3];
                sprintf(_val, "%d", alg.getValue(x, y));
                API::setText(x, y, _val);

                if (alg.getValue(x, y) > 0)
                {
                    API::setColor(x, y, 'b');
                }
            }
        }

        // Mark along the intended direction
        int startX = alg.mapPoseX;         // Current robot pose
        int startY = alg.mapPoseY;         // Current robot pose
        while (startX != 8 || startY != 8) // As long as we haven't walked to the center
        {
            if (alg.getDirection(startX, startY, 8, 8) == NORTH)
            {
                startY += 1;
                API::setColor(startX, startY, 'g');
            }
            else if (alg.getDirection(startX, startY, 8, 8) == SOUTH)
            {
                startY -= 1;
                API::setColor(startX, startY, 'g');
            }
            else if (alg.getDirection(startX, startY, 8, 8) == EAST)
            {
                startX += 1;
                API::setColor(startX, startY, 'g');
            }
            else if (alg.getDirection(startX, startY, 8, 8) == WEST)
            {
                startY -= 1;
                API::setColor(startX, startY, 'g');
            }
        }
    }
}

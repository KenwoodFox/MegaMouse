#include <iostream>
#include <string>

#include "API.h"       // MMS Simulator API
#include "algorithm.h" // On-robot algorithm

static Algorithm alg; // Create a local instance of algorithm

void log(const std::string &text)
{
    std::cerr << text << std::endl;
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
        if (!API::wallLeft())
        {
            alg.setWall(alg.mapDir);
            alg.turnLeft();
            API::turnLeft();
        }
        while (API::wallFront())
        {
            alg.setWall(alg.mapDir);
            alg.turnRight();
            API::turnRight();
        }
        API::moveForward();
        alg.forward();

        // Update the simulator with what the robot has in memory
        for (uint8_t x = 0; x < 16; x++)
        {
            for (uint8_t y = 0; y < 16; y++)
            {
                uint16_t _raw = alg.getRaw(x, y);

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
                int _num = (_raw >> 8) & 0xff;
                sprintf(_val, "%d", _num);
                API::setText(x, y, _val);
            }
        }
    }
}

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
            API::turnLeft();
        }
        while (API::wallFront())
        {
            API::turnRight();
        }
        API::moveForward();

        // Lets update the simulator display to show what the algorithm sees
        for (uint8_t x = 0; x < 16; x++)
        {
            for (uint8_t y = 0; y < 16; y++)
            {
                uint16_t _raw = alg.getRaw(x, y);
                if (_raw & (1 << 0)) // 0 is North
                {
                    API::setWall(x, y, 'n');
                }
            }
        }
    }
}

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
    API::setColor(0, 0, 'G');
    API::setText(0, 0, "abc");
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
    }
}

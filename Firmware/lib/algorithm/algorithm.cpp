#include "algorithm.h"

// Algorithm::Algorithm()
// {
//     ;
// }

void Algorithm::init()
{
    maze[4][6] = 0b1111111111111111;
}

uint16_t Algorithm::getRaw(int x, int y)
{
    if (x > 16 or y > 16)
    {
        return 0;
    }

    return maze[x][y];
}

#include "../inc/InitWindow.h"

int main()
{
    InitWindow game {2000, 1200, "Test"};

    game.run();
    
    return 0;
}

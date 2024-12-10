#include "../inc/InitWindow.h"

int main()
{
    InitWindow game {800, 600, "Test"};

    game.run();
    
    return 0;
}

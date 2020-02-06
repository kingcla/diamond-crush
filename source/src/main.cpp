#ifdef __cplusplus
    #include <cstdlib>
#else
    #include <stdlib.h>
#endif

#include "Engine.h"

int main ( int argc, char** argv )
{
    // Create the game engine
    Engine* game_core = new Engine();

    // Init the engine
    game_core->init("resources/icon.png","Diamond Crush");

    // program main loop
    while (game_core->update())
    {
        // It's out of the engine to let the programmer manage other aspects, that differs from the game
    } // end main loop

    // exit the game
    game_core->close();

    // delete the reference
    delete(game_core);

    // all is well ;)
    printf("Exited cleanly\n");
    return 0;
}



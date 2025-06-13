//needed to hide a console window
#define _WIN32_WINNT 0x0500
#include <windows.h>
#include "headers/Game.h"


int main()
{
    //needed to hide console window
    FreeConsole();

    
    Game* game = new Game();
    while (game->running())
    {
        if(!game->menuOpen() && !game->getEnd() && !game->getLose()){
            game->update();
        }
        

        game->render();
       
    }
}
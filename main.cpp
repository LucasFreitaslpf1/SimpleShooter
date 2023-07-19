#include "Game.hpp"
#include <SDL2/SDL_ttf.h>

const int FPS = 60;
const int DELAY_TIME = 100.0f / FPS;
Uint32 frameStart, frameTime;

int main(int argc, char *args[])
{
    std::cout << "Check\n";

    Game game;
    game.init("Simple Asteroids Game", SDL_WINDOWPOS_CENTERED,
              SDL_WINDOWPOS_CENTERED);

    if (TTF_Init() == -1)
    {
        return 0;
    }

    while (game.isRunning())
    {
        frameStart = SDL_GetTicks();
        game.handleEvents();
        game.update();

        frameTime = SDL_GetTicks() - frameStart;

        if (frameTime < DELAY_TIME)
        {
            SDL_Delay((int)(DELAY_TIME - frameTime));
        }
    }
    game.clean();
    return 0;
}
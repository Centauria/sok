#pragma once
#include <SDL2/SDL.h>
#include "gamemap.h"

class SDL2Engine
{
private:
    World world{"../maps/1.txt"};
    SDL_Window *window;
    SDL_Renderer *renderer;

public:
    SDL2Engine();
    ~SDL2Engine();
    void init();
    void run();
};

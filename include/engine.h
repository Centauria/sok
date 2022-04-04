#pragma once

#if defined(APPLE) || defined(MSVC)
#include <SDL.h>
#else
#include <SDL2/SDL.h>
#endif
#include "gamemap.h"

class SDL2Engine
{
private:
    World world{"maps/1.txt"};
    SDL_Window *window;
    SDL_Renderer *renderer;

public:
    SDL2Engine();
    ~SDL2Engine();
    void init();
    void run();
};

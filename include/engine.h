#pragma once

#include "gamemap.h"
#include <SDL.h>
#include <SDL2pp/SDL2pp.hh>

using namespace SDL2pp;

class SDL2Engine
{
private:
    World world{"maps/2.txt"};
    SDL sdl{SDL_INIT_VIDEO};
    std::shared_ptr<Window> window;
    std::shared_ptr<Renderer> renderer;

public:
    SDL2Engine();
    ~SDL2Engine();
    void init(int, bool, int, int);
    void run();
    void renderWorld(World world);
};

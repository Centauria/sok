#pragma once

#include "gamemap.h"
#include "load.h"

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
    Loader loader{"resources.pac"};
    std::unordered_map<TileType, std::string> resource_map{
            {Target,       "target.svg"},
            {TargetPlayer, "target-player.svg"},
            {TargetBox,    "target-box.svg"},
            {Box,          "box.svg"},
            {Player,       "player.svg"},
            {Wall,         "wall.svg"},
    };
public:
    SDL2Engine() = default;
    ~SDL2Engine() = default;
    void init(int, bool, int, int);
    void run();
    void renderWorld(World world);
    [[nodiscard]] Loader getLoader() const;
};

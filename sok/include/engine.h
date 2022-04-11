#pragma once

#include "gamemap.h"
#include "load.h"

#include <memory>
#include <SDL.h>
#include <SDL2pp/SDL2pp.hh>

using namespace SDL2pp;

class SDL2Engine
{
private:
    World world{"maps/2.txt"};
    SDL sdl{SDL_INIT_VIDEO | SDL_INIT_AUDIO};
    SDLMixer mix{MIX_INIT_OGG | MIX_INIT_MP3};
    std::shared_ptr<Window> window;
    std::shared_ptr<Renderer> renderer;
    Mixer mixer{44100,
                MIX_DEFAULT_FORMAT,
                MIX_DEFAULT_CHANNELS,
                128};
    Loader loader{"resources.pac"};
    std::unordered_map<TileType, std::string> resource_map{
            {Target,       "img/target.svg"},
            {TargetPlayer, "img/target-player.svg"},
            {TargetBox,    "img/target-box.svg"},
            {Box,          "img/box.svg"},
            {Player,       "img/player.svg"},
            {Wall,         "img/wall.svg"},
    };
    std::unordered_map<TileType, std::shared_ptr<lunasvg::Bitmap>> entity_map{};
    int current_window_w{}, current_window_h{};

public:
    SDL2Engine() = default;
    ~SDL2Engine() = default;
    void init(int, bool, int, int);
    void run();
    void renderWorld(World world);
    [[nodiscard]] Loader getLoader() const;
};

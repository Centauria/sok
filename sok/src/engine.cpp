#include "engine.h"


void SDL2Engine::init(int displayID, bool is_fullscreen, int window_height, int window_width)
{
    int rendererFlags, windowFlags;
    rendererFlags = SDL_RENDERER_ACCELERATED;
    windowFlags = is_fullscreen ? SDL_WINDOW_FULLSCREEN : SDL_WINDOW_RESIZABLE;

    int displays = SDL_GetNumVideoDisplays();
    if (displays <= 0)
    {
        std::cerr << SDL_GetError() << std::endl;
        exit(1);
    }
    std::vector<SDL_Rect> displayBounds;
    for (int i = 0; i < displays; i++)
    {
        displayBounds.emplace_back();
        SDL_GetDisplayBounds(i, &displayBounds.back());
    }
    if (displayID >= displays)
    {
        displayID = 0;
    }
    if (is_fullscreen)
    {
        window_width = displayBounds[displayID].w;
        window_height = displayBounds[displayID].h;
    }
    window = std::make_shared<Window>(
            Window("Sok",
                   displayBounds[displayID].x + 100, displayBounds[displayID].y + 100,
                   window_width, window_height,
                   windowFlags));
    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "linear");
    renderer = std::make_shared<Renderer>(Renderer(*window, -1, rendererFlags));
    world.print();
    current_window_h = window->GetHeight();
    current_window_w = window->GetWidth();
}

void SDL2Engine::run()
{
    bool is_running = true;
    playOGG("snd/work-loop.ogg");
    SDL_Event event;
    while (is_running)
    {
        if (current_window_h != window->GetHeight() || current_window_w != window->GetWidth())
        {
            entity_map.clear();
        }
        renderer->SetDrawColor(96, 128, 255, 255);
        renderer->Clear();
        renderWorld(world);
        renderer->Present();
        while (SDL_PollEvent(&event))
        {
            switch (event.type)
            {
            case SDL_QUIT:
                is_running = false;
                break;
            case SDL_KEYUP:
                switch (SDL_GetScancodeFromKey(event.key.keysym.sym))
                {
                case SDL_SCANCODE_W:
                    world.take(Action::Up);
                    break;
                case SDL_SCANCODE_S:
                    world.take(Action::Down);
                    break;
                case SDL_SCANCODE_A:
                    world.take(Action::Left);
                    break;
                case SDL_SCANCODE_D:
                    world.take(Action::Right);
                    break;
                case SDL_SCANCODE_R:
                    world = World{"maps/2.txt"};
                default:
                    break;
                }
            default:
                break;
            }
        }
        SDL_Delay(16);
    }
}

void SDL2Engine::renderWorld(World world)
{
    auto data = world.getData();
    for (int i = 0; i < world.getHeight(); i++)
    {
        for (int j = 0; j < world.getWidth(); j++)
        {
            auto tt = (TileType) data[i][j];
            auto xpath = resource_map[tt];
            if (!xpath.empty())
            {
                const auto rect = World::cellRect(
                        i, j, window->GetDrawableHeight(), window->GetDrawableWidth(),
                        world.getHeight(), world.getWidth());
                if (entity_map.find(tt) == entity_map.end())
                {
                    entity_map[tt] = loader.getSVG(xpath)->getBitmap(rect->w, rect->h);
                }
                auto *const pSurface = new SDL2pp::Surface(
                        static_cast<void *>(entity_map[tt]->data()),
                        rect->w, rect->h, 32, entity_map[tt]->stride(),
                        0x000000ff, 0x0000ff00, 0x00ff0000, 0xff000000);
                auto texture = SDL2pp::Texture(*renderer, *pSurface);
                renderer->Copy(texture, NullOpt, SDL2pp::Point{rect->x, rect->y});
                delete pSurface;
            }
        }
    }
}

Loader SDL2Engine::getLoader() const
{
    return loader;
}

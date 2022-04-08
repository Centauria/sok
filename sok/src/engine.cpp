#include "engine.h"

SDL2Engine::SDL2Engine() = default;

SDL2Engine::~SDL2Engine() = default;

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
}

void SDL2Engine::run()
{
    bool is_running = true;
    SDL_Event event;
    while (is_running)
    {
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
            switch (data[i][j])
            {
            case Target:
                renderer->SetDrawColor(0, 255, 0, SDL_ALPHA_OPAQUE);
                break;
            case Player:
            case TargetPlayer:
                renderer->SetDrawColor(255, 0, 0, SDL_ALPHA_OPAQUE);
                break;
            case Box:
            case TargetBox:
                renderer->SetDrawColor(0, 255, 255, SDL_ALPHA_OPAQUE);
                break;
            case None:
                renderer->SetDrawColor(244, 255, 244, SDL_ALPHA_OPAQUE);
                break;
            case Wall:
                renderer->SetDrawColor(0, 0, 0, SDL_ALPHA_OPAQUE);
                break;
            default:
                break;
            }
            auto rect = World::cellRect(
                    i, j, window->GetDrawableHeight(), window->GetDrawableWidth(),
                    world.getHeight(), world.getWidth());
            renderer->FillRect(*rect);
        }
    }
}

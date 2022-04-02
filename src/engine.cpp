#include "engine.h"

#define SCREEN_WIDTH 1280
#define SCREEN_HEIGHT 720

SDL2Engine ::SDL2Engine(/* args */)
{
}

SDL2Engine ::~SDL2Engine()
{
}

void SDL2Engine::init()
{
    int rendererFlags, windowFlags;

    rendererFlags = SDL_RENDERER_ACCELERATED;

    windowFlags = 0;

    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        printf("Couldn't initialize SDL: %s\n", SDL_GetError());
        exit(1);
    }

    window = SDL_CreateWindow("Shooter 01", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, windowFlags);

    if (!window)
    {
        printf("Failed to open %d x %d window: %s\n", SCREEN_WIDTH, SCREEN_HEIGHT, SDL_GetError());
        exit(1);
    }

    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "linear");

    renderer = SDL_CreateRenderer(window, -1, rendererFlags);

    if (!renderer)
    {
        printf("Failed to create renderer: %s\n", SDL_GetError());
        exit(1);
    }
    world.print();
}

void SDL2Engine::run()
{
    bool is_running = true;
    SDL_Event event;
    while (is_running)
    {
        SDL_SetRenderDrawColor(renderer, 96, 128, 255, 255);
        SDL_RenderClear(renderer);
        world.render(renderer, SCREEN_WIDTH, SCREEN_HEIGHT);
        SDL_RenderPresent(renderer);
        while (SDL_PollEvent(&event))
        {
            switch (event.type)
            {
            case SDL_QUIT:
                exit(0);
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
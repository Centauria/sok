#pragma once
#include <SDL2/SDL.h>
#include <string>
#include "array.hpp"

#define HEIGHT 8
#define WIDTH 8

using namespace lite;

enum TileType
{
    Target = -3,
    TargetPlayer,
    TargetBox,
    None,
    Box,
    Player,
    Wall,
};

enum class Action
{
    Up = 0,
    Down,
    Left,
    Right
};

class World
{
private:
    array<int[8][8]> data;

public:
    World(std::string);
    ~World();
    std::vector<int> getPlayerPos();
    void take(Action);
    void print();
    SDL_Rect* cellRect(int, int, int, int);
    void render(SDL_Renderer*, int, int);
};

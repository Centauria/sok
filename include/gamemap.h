#pragma once

#include <SDL.h>
#include <string>
#include <vector>


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
    std::vector<std::vector<int>> data;
    int height{};
    int width{};

public:
    explicit World(const std::string &);
    ~World();
    std::vector<int> getPlayerPos();
    void take(Action);
    void print();
    static SDL_Rect *cellRect(int, int, int, int);
    void render(SDL_Renderer *, int, int);
};

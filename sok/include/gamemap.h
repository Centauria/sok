#pragma once

#include <SDL.h>
#include <SDL2pp/SDL2pp.hh>
#include <string>
#include <vector>
#include <memory>

using namespace SDL2pp;


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
    size_t height{};
    size_t width{};

public:
    explicit World(const std::string &);
    ~World();
    std::vector<int> getPlayerPos();
    void take(Action);
    void print();
    static std::shared_ptr<SDL_Rect> cellRect(int y, int x, int sh, int sw, int h, int w);
    [[nodiscard]] int getHeight() const;
    [[nodiscard]] int getWidth() const;
    [[nodiscard]] const std::vector<std::vector<int>> &getData() const;
};

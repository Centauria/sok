#include "gamemap.h"
#include "util.h"

#include "SDL2pp/SDL2pp.hh"
#include <iostream>

using namespace SDL2pp;


World::World(const std::string &filepath)
{
    auto content = file_contents(filepath);
    auto ss = split(content, "\n");
    for (const auto &line: ss)
    {
        std::vector<int> lyne{};
        auto e = split(line, ",");
        for (const auto &c: e)
        {
            lyne.push_back(std::stoi(c));
        }
        data.push_back(lyne);
    }
    height = data.size();
    width = data[0].size();
}

World::~World() = default;

std::vector<int> World::getPlayerPos()
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            if (data[i][j] == Player || data[i][j] == TargetPlayer)
                return std::vector<int>{i, j};
        }
    }
    return std::vector<int>{-1, -1};
}

void World::take(Action action)
{
    auto x = this->getPlayerPos();
    auto playerStatus = data[x[0]][x[1]];

    int dx{}, dy{};
    switch (action)
    {
    case Action::Up:
        dx = -1;
        break;
    case Action::Down:
        dx = 1;
        break;
    case Action::Left:
        dy = -1;
        break;
    case Action::Right:
        dy = 1;
        break;
    }
    switch (data[x[0] + dx][x[1] + dy])
    {
    case Target:
        data[x[0] + dx][x[1] + dy] = TargetPlayer;
        if (playerStatus == TargetPlayer)
            data[x[0]][x[1]] = Target;
        else
            data[x[0]][x[1]] = None;
        break;
    case TargetBox:
        switch (data[x[0] + 2 * dx][x[1] + 2 * dy])
        {
        case Target:
            data[x[0] + 2 * dx][x[1] + 2 * dy] = TargetBox;
            data[x[0] + dx][x[1] + dy] = TargetPlayer;
            if (playerStatus == TargetPlayer)
                data[x[0]][x[1]] = Target;
            else
                data[x[0]][x[1]] = None;
            break;
        case TargetBox:
        case Box:
        case Wall:
            break;
        case None:
            data[x[0] + 2 * dx][x[1] + 2 * dy] = Box;
            data[x[0] + dx][x[1] + dy] = TargetPlayer;
            if (playerStatus == TargetPlayer)
                data[x[0]][x[1]] = Target;
            else
                data[x[0]][x[1]] = None;
            break;
        }
        break;
    case None:
        data[x[0] + dx][x[1] + dy] = Player;
        if (playerStatus == TargetPlayer)
            data[x[0]][x[1]] = Target;
        else
            data[x[0]][x[1]] = None;
        break;
    case Box:
        switch (data[x[0] + 2 * dx][x[1] + 2 * dy])
        {
        case Target:
            data[x[0] + 2 * dx][x[1] + 2 * dy] = TargetBox;
            data[x[0] + dx][x[1] + dy] = Player;
            if (playerStatus == TargetPlayer)
                data[x[0]][x[1]] = Target;
            else
                data[x[0]][x[1]] = None;
            break;
        case TargetBox:
        case Box:
        case Wall:
            break;
        case None:
            data[x[0] + 2 * dx][x[1] + 2 * dy] = Box;
            data[x[0] + dx][x[1] + dy] = Player;
            if (playerStatus == TargetPlayer)
                data[x[0]][x[1]] = Target;
            else
                data[x[0]][x[1]] = None;
            break;
        }
        break;
    case Wall:
        break;
    }
}

void World::print()
{
    for (const auto &x: data)
    {
        for (auto y: x)
        {
            std::cout << y << ",";
        }
        std::cout << std::endl;
    }
}

std::unique_ptr<SDL_Rect> World::cellRect(int y, int x, int sh, int sw, int h, int w)
{
    int d = (int) ((sh / h) < (sw / w) ? sh / h : sw / w);
    int x0 = (int) ((sw - w * d) / 2);
    int y0 = (int) ((sh - h * d) / 2);

    return std::make_unique<SDL_Rect>(SDL_Rect{x0 + x * d, y0 + y * d, d, d});
}

int World::getHeight() const
{
    return height;
}
int World::getWidth() const
{
    return width;
}
const std::vector<std::vector<int>> &World::getData() const
{
    return data;
}

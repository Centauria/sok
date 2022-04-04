#include "gamemap.h"
#include "array.hpp"
#include "util.h"

#include <filesystem>
#include <fstream>
#include <iostream>
#include <vector>


using namespace lite;

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
    for (auto x: data)
    {
        for (auto y: x)
        {
            std::cout << y << ",";
        }
        std::cout << std::endl;
    }
}

SDL_Rect *World::cellRect(int x, int y, int sh, int sw)
{
    int x0 = sw / 2 - 300;
    int y0 = sh / 2 - 300;
    int d = 600 / 8;

    return new SDL_Rect{y0 + y * d, x0 + x * d, d, d};
}

void World::render(SDL_Renderer *renderer, int sh, int sw)
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            switch (data[i][j])
            {
            case Target:
                SDL_SetRenderDrawColor(renderer, 0, 255, 0, SDL_ALPHA_OPAQUE);
                break;
            case Player:
            case TargetPlayer:
                SDL_SetRenderDrawColor(renderer, 255, 0, 0, SDL_ALPHA_OPAQUE);
                break;
            case Box:
            case TargetBox:
                SDL_SetRenderDrawColor(renderer, 0, 255, 255, SDL_ALPHA_OPAQUE);
                break;
            case None:
                SDL_SetRenderDrawColor(renderer, 244, 255, 244, SDL_ALPHA_OPAQUE);
                break;
            case Wall:
                SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
                break;
            default:
                break;
            }
            auto rect = cellRect(i, j, sh, sw);
            SDL_RenderFillRect(renderer, rect);
            delete rect;
        }
    }
}
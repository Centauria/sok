//
// Created by Centauria V. CHEN on 2022/4/11.
//
#pragma once

#include <vector>
#include <lunasvg.h>
#include <SDL2pp/SDL2pp.hh>

class Data
{
public:
    virtual ~Data() = default;
};

class DataSVG : public Data
{
private:
    std::shared_ptr<lunasvg::Document> document;
public:
    explicit DataSVG(std::vector<char> data);
    [[nodiscard]] SDL2pp::Surface *getSurface(uint32_t width, uint32_t height) const;
};

class DataOGG : public Data
{
private:
    std::vector<char> data;
public:
    explicit DataOGG(std::vector<char> data) : data(data)
    {};
    [[nodiscard]] std::shared_ptr<SDL2pp::Music> getMusic();
    [[nodiscard]] std::shared_ptr<SDL2pp::Chunk> getChunk();
    std::string to_string();
};
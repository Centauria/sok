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
    explicit DataSVG(std::vector<uint8_t> data);
    explicit DataSVG(const std::string &filename);
    [[nodiscard]] std::shared_ptr<lunasvg::Bitmap> getBitmap(uint32_t width, uint32_t height) const;
};

class DataOGG : public Data
{
private:
    std::vector<uint8_t> data{};
    std::string filename{};

public:
    explicit DataOGG(std::vector<uint8_t> data) : data(data)
    {};

    explicit DataOGG(std::string filename) : filename(std::move(filename))
    {};
    [[nodiscard]] std::vector<uint8_t> getData();
};
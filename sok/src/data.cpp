//
// Created by Centauria V. CHEN on 2022/4/11.
//

#include "data.h"

DataSVG::DataSVG(std::vector<char> data)
{
    document = std::move(lunasvg::Document::loadFromData(std::string(data.begin(), data.end())));
}

SDL2pp::Surface DataSVG::getSurface(uint32_t width, uint32_t height)
{
    auto bitmap = document->renderToBitmap(width, height);
    auto surface = SDL2pp::Surface(
            bitmap.data(),
            width, height, 8, sizeof(typeof(*bitmap.data())) * width,
            0xff000000, 0x00ff0000, 0x0000ff00, 0x000000ff);
    return surface;
}

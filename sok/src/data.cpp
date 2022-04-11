//
// Created by Centauria V. CHEN on 2022/4/11.
//

#include "data.h"

DataSVG::DataSVG(std::vector<char> data)
{
    document = lunasvg::Document::loadFromData(std::string(data.begin(), data.end()));
}

SDL2pp::Surface *DataSVG::getSurface(uint32_t width, uint32_t height) const
{
    auto bitmap = document->renderToBitmap(width, height); // TODO: Fix the issue that bitmap.data() returns NULL
    if (!bitmap.valid())
    {
        throw std::runtime_error("failed to create bitmap");
    }
    const auto surface = new SDL2pp::Surface(
            static_cast<void *>(bitmap.data()),
            width, height, 32, bitmap.stride(),
            0x000000ff, 0x0000ff00, 0x00ff0000, 0xff000000);
    return surface;
}
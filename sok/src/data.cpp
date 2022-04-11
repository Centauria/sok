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

std::shared_ptr<SDL2pp::Music> DataOGG::getMusic()
{
    auto container_ops = SDL2pp::ContainerRWops<std::vector<char>>(data);
    auto ops = SDL2pp::RWops{std::move(container_ops)};
    return std::make_shared<SDL2pp::Music>(SDL2pp::Music(ops, MUS_OGG));
}

std::shared_ptr<SDL2pp::Chunk> DataOGG::getChunk()
{
    auto container_ops = SDL2pp::ContainerRWops<std::vector<char>>(data);
    auto ops = SDL2pp::RWops{std::move(container_ops)};
    return std::make_shared<SDL2pp::Chunk>(SDL2pp::Chunk(ops));
}

std::string DataOGG::to_string()
{
    auto result = "data size: " + std::to_string(data.size()) + " [";
    for (auto i = 0; i < 3; i++)
    {
        result += std::to_string(data[i]);
        result += ",";
    }
    result += "... ,";
    for (auto i = 1; i < 4; i++)
    {
        result += std::to_string(data[data.size() - i]);
        result += ",";
    }
    result += "]";
    return result;
}

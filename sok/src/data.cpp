//
// Created by Centauria V. CHEN on 2022/4/11.
//

#include "data.h"

DataSVG::DataSVG(std::vector<uint8_t> data)
{
    document = lunasvg::Document::loadFromData(std::string(data.begin(), data.end()));
}

DataSVG::DataSVG(const std::string &filename)
{
    document = lunasvg::Document::loadFromFile(filename);
}

std::shared_ptr<lunasvg::Bitmap> DataSVG::getBitmap(uint32_t width, uint32_t height) const
{
    return std::make_shared<lunasvg::Bitmap>(document->renderToBitmap(width, height));
}

std::vector<uint8_t> DataOGG::getData()
{
    return std::vector<uint8_t>{data};
}
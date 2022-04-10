//
// Created by Centauria V. CHEN on 2022/4/10.
//

#include "load.h"
#include "util.h"

#include <fstream>
#include <memory>
#include <vector>
#include <stdexcept>

void Loader::load_items()
{
    std::ifstream loader(path, std::ios::in | std::ios::binary);
    if (loader.is_open())
    {
        ResourceHeader header{};
        loader.read(reinterpret_cast<char *>(&header.signature), sizeof(header.signature));
        loader.read(reinterpret_cast<char *>(&header.index_length), sizeof(header.index_length));
        for (int item = 0; item < header.index_length; item++)
        {
            ResourceItem resource;
            std::vector<char> s;
            char e{};
            loader.read(reinterpret_cast<char *>(&e), 1);
            while (e != '\0')
            {
                s.push_back(e);
                loader.read(reinterpret_cast<char *>(&e), 1);
            }
            std::string ss(s.begin(), s.end());
            resource.xpath = ss;
            loader.read(reinterpret_cast<char *>(&resource.filesize), sizeof(resource.filesize));
            loader.read(reinterpret_cast<char *>(&resource.start_offset), sizeof(resource.start_offset));
            items[ss] = resource;
        }
        initial_offset = loader.tellg();
        loader.close();
    } else
    {
        throw std::runtime_error("error loading " + path);
    }
}

template<class Tp>
Tp &Loader::get(const std::string &xpath)
{
    auto ext = split(xpath, ".")[-1];
    return nullptr;
}

std::shared_ptr<std::vector<char>> Loader::read(const std::string &xpath)
{
    std::ifstream loader(path, std::ios::in | std::ios::binary);
    auto item = items[xpath];
    auto offset = initial_offset + item.start_offset;
    loader.seekg(offset, loader.beg);
    std::vector<char> vc;
    if (!loader.read(vc.data(), item.filesize))
    {
        throw std::runtime_error("error reading data from offset" + std::to_string(offset));
    }
    return std::make_shared<std::vector<char>>(vc);
}

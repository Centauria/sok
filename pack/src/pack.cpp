//
// Created by Centauria V. CHEN on 2022/4/8.
//

#include "pack.h"

#include <iostream>
#include <fstream>
#include <filesystem>
#include <regex>

namespace fs = std::filesystem;

std::vector<ResourceItem> scan(const std::string &path)
{
    std::vector<ResourceItem> res{};
    uint64_t offset = 0;
    for (auto &e: fs::recursive_directory_iterator(path))
    {
        auto fp = e.path();
        if (fs::is_regular_file(fp))
        {
            auto size = fs::file_size(fp);
            auto xpath = std::regex_replace(fp.string(), std::regex{"^" + path}, "");
            xpath = std::regex_replace(xpath, std::regex{"^/"}, "");
            std::cout << fp << " -> " << xpath << std::endl;
            ResourceItem item{xpath, size, offset};
            res.push_back(item);
            offset += size;
        }
    }
    return res;
}

void write_file(std::string path, uint16_t signature, std::string filename, std::vector<ResourceItem> items)
{
    std::ofstream pack(filename, std::ios::out | std::ios::binary);
    if (pack.is_open())
    {
        ResourceHeader header{signature, static_cast<uint32_t>(items.size())};
        pack.write((char *) (&header), sizeof(ResourceHeader));
        for (auto item: items)
        {
            pack.write((char *) (&item), sizeof(ResourceItem));
        }
        auto pack_buf = std::ostreambuf_iterator<char>(pack);
        for (const auto &item: items)
        {
            auto item_path = fs::path(path) / item.xpath;
            std::cout << "item path: " << item_path << std::endl;
            std::ifstream reader(item_path, std::ios::in | std::ios::binary);
            std::istreambuf_iterator<char> begin(reader), end;
            std::copy(begin, end, pack_buf);
            reader.close();
        }
        pack.close();
    } else
    {
        std::cerr << "unable to open file " << filename << std::endl;
    }
}

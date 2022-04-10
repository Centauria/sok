//
// Created by Centauria V. CHEN on 2022/4/10.
//
#pragma once

#include "pack.h"

#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <lunasvg.h>

class Loader
{
private:
    std::string path;
    std::unique_ptr<std::vector<ResourceItem>> items;
    std::unordered_map<std::string, ResourceItem> item_map;
public:
    explicit Loader(std::string path) : path(std::move(path)), items()
    {};
    ~Loader() = default;
    void load_items();
    template<class Tp>
    Tp &get(const std::string &xpath);
};
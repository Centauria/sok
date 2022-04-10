//
// Created by Centauria V. CHEN on 2022/4/10.
//
#pragma once

#include "pack.h"

#include <string>
#include <utility>
#include <vector>
#include <memory>

class Loader
{
private:
    std::string path;
    std::unique_ptr<std::vector<ResourceItem>> items;
public:
    explicit Loader(std::string path) : path(std::move(path)), items()
    {};
    ~Loader() = default;
    void load_items();
};
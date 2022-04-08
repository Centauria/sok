//
// Created by Centauria V. CHEN on 2022/4/8.
//
#pragma once

#include <filesystem>
#include "blobify/blobify.hpp"

enum class ResourceType
{
    image = 0,
    sound,
};

struct ResourceItem
{
    std::string xpath;
    ResourceType xtype;
    uint64_t start_offset;
    uint64_t end_offset;
};

struct ResourceHeader
{
    uint16_t signature;
    uint32_t index_length;
};
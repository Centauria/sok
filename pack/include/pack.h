//
// Created by Centauria V. CHEN on 2022/4/8.
//
#pragma once

#include <string>
#include <vector>
#include <filesystem>

struct ResourceItem
{
    std::string xpath;
    uint64_t filesize;
    uint64_t start_offset;
};

struct ResourceHeader
{
    uint32_t signature;
    uint32_t index_length;
};

/* The format of resource pack file
 *
 * {ResourceHeader, [ResourceItem * index_length], [data blob]}
 *
 */

std::vector<ResourceItem> scan(const std::string &);

void write_file(const std::string&, uint16_t, const std::string&, const std::vector<ResourceItem>&);

//
// Created by Centauria V. CHEN on 2022/4/10.
//
#pragma once

#include "pack.h"
#include "util.h"
#include "data.h"

#include <string>
#include <utility>
#include <vector>
#include <memory>
#include <unordered_map>
#include <lunasvg.h>

class Loader
{
private:
    std::string path;
    std::unordered_map<std::string, ResourceItem> items{};
    size_t initial_offset{};
public:
    explicit Loader(std::string path) : path(std::move(path))
    { load_items(); };
    ~Loader() = default;
    void load_items();
    [[nodiscard]] std::vector<std::string> keys() const;
    std::shared_ptr<std::vector<uint8_t>> read(const std::string &xpath);
    std::shared_ptr<DataSVG> getSVG(const std::string &xpath, bool use_pac = true);
    std::shared_ptr<DataOGG> getOGG(const std::string &xpath, bool use_pac = true);
};

class Processor
{
private:
public:
    virtual ~Processor() = default;
    virtual void process() const = 0;
};

using ProcessorPtr = std::shared_ptr<Processor>;

class ProcessorSVG : public Processor
{
public:
    virtual void process() const override
    {};
};
#pragma once

#include <filesystem>
#include <string>
#include <vector>

std::string file_contents(const std::filesystem::path &path);
std::vector<std::string> split(const std::string &str, const std::string &delim);
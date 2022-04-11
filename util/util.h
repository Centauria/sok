#pragma once

#include <filesystem>
#include <string>
#include <vector>

using namespace std::string_literals;

std::string file_contents(const std::filesystem::path &path);
std::vector<std::string> split(const std::string &str, const std::string &delim);
std::string split_ext(const std::string &str);
void ltrim(std::string &s, const std::string &chars = ""s);
void rtrim(std::string &s, const std::string &chars = ""s);
void trim(std::string &s, const std::string &chars = ""s);
std::string ltrim_copy(std::string s, const std::string &chars = ""s);
std::string rtrim_copy(std::string s, const std::string &chars = ""s);
std::string trim_copy(std::string s, const std::string &chars = ""s);
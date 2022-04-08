#include "util.h"

#include <filesystem>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <cctype>
#include <locale>

/**
 * Returns an std::string which represents the raw bytes of the file.
 *
 * @param path The path to the file.
 * @return The content of the file as it resides on the disk - byte by byte.
 */
std::string file_contents(const std::filesystem::path &path)
{
    // Sanity check
    if (!std::filesystem::is_regular_file(path))
        return {"Irregular"};
    // Open the file
    // Note that we have to use binary mode as we want to return a string
    // representing matching the bytes of the file on the file system.
    std::ifstream file(path, std::ios::in | std::ios::binary);
    if (!file.is_open())
        return {"Not open"};

    // Read contents
    const std::size_t &size = std::filesystem::file_size(path);
    std::string content(size, '\0');
    file.read(content.data(), size);

    // Close the file
    file.close();

    return content;
}

std::vector<std::string> split(const std::string &str, const std::string &delim)
{
    std::vector<std::string> res;
    if (str.empty())
        return res;
    std::string strs = str + delim;
    size_t pos = strs.find(delim);
    while (pos != std::string::npos)
    {
        auto temp = strs.substr(0, pos);
        res.push_back(temp);
        strs = strs.substr(pos + 1, strs.size());
        pos = strs.find(delim);
    }
    return res;
}

// trim from start (in place)
void ltrim(std::string &s, const std::string &chars)
{
    s.erase(s.begin(), std::find_if(s.begin(), s.end(), [&chars](unsigned char ch)
    {
        return chars.empty() ? !std::isspace(ch) : chars.find(ch) == std::string::npos;
    }));
}

// trim from end (in place)
void rtrim(std::string &s, const std::string &chars)
{
    s.erase(std::find_if(s.rbegin(), s.rend(), [&chars](unsigned char ch)
    {
        return chars.empty() ? !std::isspace(ch) : chars.find(ch) == std::string::npos;
    }).base(), s.end());
}

// trim from both ends (in place)
void trim(std::string &s, const std::string &chars)
{
    ltrim(s, chars);
    rtrim(s, chars);
}

// trim from start (copying)
std::string ltrim_copy(std::string s, const std::string &chars)
{
    ltrim(s, chars);
    return s;
}

// trim from end (copying)
std::string rtrim_copy(std::string s, const std::string &chars)
{
    rtrim(s, chars);
    return s;
}

// trim from both ends (copying)
std::string trim_copy(std::string s, const std::string &chars)
{
    trim(s, chars);
    return s;
}
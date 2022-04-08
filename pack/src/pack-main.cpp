//
// Created by Centauria V. CHEN on 2022/4/8.
//

#include "pack.h"

#include <string>
#include <filesystem>
#include "argparse/argparse.hpp"

using namespace std::string_literals;

namespace fs = std::filesystem;

int main(int argc, const char *argv[])
{
    argparse::ArgumentParser parser("pack");
    parser.add_argument("resources")
            .help("specify path to resources folder");
    parser.add_argument("-o", "--output")
            .help("output file path")
            .default_value("output.pac"s);
    try
    {
        parser.parse_args(argc, argv);
    }
    catch (const std::runtime_error &err)
    {
        std::cerr << err.what() << std::endl;
        std::cerr << parser;
        std::exit(1);
    }

    auto resources = parser.get<std::string>("resources");
    auto output = parser.get<std::string>("--output");
    if (fs::is_directory(resources))
    {
        auto items = scan(resources);
        write_file(resources, 0x163f, output, items);
    }
    return 0;
}
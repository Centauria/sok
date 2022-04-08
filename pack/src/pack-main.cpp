//
// Created by Centauria V. CHEN on 2022/4/8.
//

#include "pack.h"

#include <filesystem>
#include "blobify/blobify.hpp"
#include "argparse/argparse.hpp"

namespace fs = std::filesystem;

int main(int argc, const char *argv[])
{
    argparse::ArgumentParser parser("pack");
    parser.add_argument("resources")
            .help("specify path to resources folder");
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
    std::cout << fs::current_path() << std::endl;
    if (fs::is_directory(resources))
    {
        for (auto &e: fs::recursive_directory_iterator(resources))
        {
            auto fp = e.path();
            std::cout << fp << std::endl;
        }
    }
    return 0;
}
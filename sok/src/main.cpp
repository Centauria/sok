#include "engine.h"
#include "data.h"

#include <iostream>
#include <INIReader.h>

#undef main //This line is for GCC on Windows

int main(int argc, char *argv[])
{
    INIReader reader("config/settings.ini");
    if (reader.ParseError() != 0)
    {
        std::cerr << "Can't load 'settings.ini'" << std::endl;
        return 1;
    }

    SDL2Engine engine{};
    auto ks = engine.getLoader().keys();
    for (const auto &k: ks)
    {
        auto data = engine.getLoader().getSVG(k);
        std::cout << k << std::endl;
    }
    engine.init(
            reader.GetInteger("screen", "monitor", 0),
            reader.GetBoolean("screen", "fullscreen", false),
            reader.GetInteger("screen", "screen_height", 1280),
            reader.GetInteger("screen", "screen_width", 720)
    );
    engine.run();
    return 0;
}

/*  TODO: handle long press event
        support action undo
*/
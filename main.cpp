#include <iostream>
#include "engine.h"
#include "gamemap.h"

#undef main //This line is for GCC on Windows

int main(int argc, char *argv[])
{
    SDL2Engine engine{};
    engine.init();
    engine.run();
    return 0;
}

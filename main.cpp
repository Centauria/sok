#include <iostream>
#include "engine.h"
#include "gamemap.h"

int main(int, char **)
{
    SDL2Engine engine{};
    engine.init();
    engine.run();
    return 0;
}

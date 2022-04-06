# sok

A try for sokoban using SDL2.

## Note

When compiling on Windows, make sure to pass value to cmake variable <SDL2_PATH>.

Particularly, when using VSCode, write or add this item to .vscode/settings.json:

"cmake.configureSettings": {"SDL2_PATH": "E:\\Path\\to\\SDL2"}

if there is no this file, create it.

## MinGW on windows

When using MinGW to compile on Windows, this program will immediately return in the console, and will not create any output. But the graphic window works fine.

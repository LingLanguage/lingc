#include <raylib.h>
#include <stdio.h>
#include "Generic.h"

int main(int argc, char **argv) {
    string str = "Hello, world!%d\n";
    PLog(str,4);
#if DEBUG_DRAW
    InitWindow(800, 600, "Hello, world!");
    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(RAYWHITE);
        EndDrawing();
    }
    CloseWindow();
#endif
    return 0;
}
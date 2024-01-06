#include "Generic.h"
#include "Helper/FileHelper.h"
#include <raylib.h>
#include <stdio.h>

int main(int argc, char **argv) {
    char *files[100000];
    const char *dir = GetWorkingDirectory();
    const char *root = TextFormat("%s\\%s", dir, "tests");
    PLog("root: %s\r\n", root);
    int count = File_RecursiveGetFilesByExtension(root, ".ling", 0, files);
    for (int i = 0; i < count; i++) {
        // readfile, tokenize, parse, compile
        printf("found: %s\n", files[i]);
    }

    // free
    for (int i = 0; i < count; i++) {
        free(files[i]);
    }

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
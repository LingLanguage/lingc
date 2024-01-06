#include "Business/export.h"
#include "Generic.h"
#include "Helper/FileHelper.h"
#include <raylib.h>
#include <stdio.h>

int main(int argc, char **argv) {

    Context *ctx = calloc(1, sizeof(Context));
    Context_Init(ctx);

    string files[100000];
    const string dir = GetWorkingDirectory();
    const string root = TextFormat("%s\\%s\\%s", dir, "tests", "src");
    PLog("root: %s\r\n", root);
    int count = File_RecursiveGetFilesByExtension(root, ".ling", 0, files);
    for (int i = 0; i < count; i++) {

        // readfile
        FILE *fp = fopen(files[i], "r");
        if (fp == NULL) {
            PLog("file not found: %s\n", files[i]);
            continue;
        }

        string str = NULL;
        long size = File_ReadAllText(fp, &str);
        // PLog("%s code: \r\n%s\r\n", files[i], str);

        // tokenize
        PLog("%s SeqMove\r\n", files[i]);
        B_Tokenize_SeqMove(ctx, str, size);

        fclose(fp);
        free(str);
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
    free(ctx);
    return 0;
}
#include "Business/export.h"
#include "Generic/StringCommon.h"
#include "Helper/FileHelper.h"
#include <raylib.h>
#include <stdio.h>

int main(int argc, char **argv) {

    StringCommon_Init();

    Context *ctx = calloc(1, sizeof(Context));
    Context_Init(ctx);

    string files[100000];
    const string dir = GetWorkingDirectory();
    const string root = TextFormat("%s\\%s\\%s", dir, "tests", "src");
    // PLog("root: %s\r\n", root);
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

        // doc
        E_Doc *doc = calloc(1, sizeof(E_Doc));
        Context_AddDoc(ctx, doc);

        // tokenize
        B_Tokenize_SeqMove(doc, files[i], str, size);

        fclose(fp);
        free(str);
    }

    // free string memory
    for (int i = 0; i < count; i++) {
        free(files[i]);
    }
#define DEBUG_DOC
#ifdef DEBUG_DOC
    for (int i = 0; i < ctx->docs_count; i++) {
        E_Doc *doc = ctx->docs[i];
        E_Doc_Log(doc);
    }
#endif

#ifdef DEBUG_DRAW
    InitWindow(800, 600, "Hello, world!");
    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(RAYWHITE);
        EndDrawing();
    }
    CloseWindow();
#endif
    Context_Free(ctx);
    printf("Compile Done!\r\n");
    return 0;
}
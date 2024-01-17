#include "Compiler.h"

void Compile(const char *root) {

    Context *ctx = calloc(1, sizeof(Context));
    Context_Init(ctx);

    CTX_Tokenize *ctx_tokenize = calloc(1, sizeof(CTX_Tokenize));
    CTX_Tokenize_Init(ctx_tokenize);

    // PLog("root: %s\r\n", root);
    string files[100000];
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
        PLog("\r\nfile begin: %s\r\n", files[i]);
        E_Doc *doc = calloc(1, sizeof(E_Doc));
        Context_AddDoc(ctx, doc);

        // tokenize
        B_Tokenize_SeqMove(ctx_tokenize, doc, files[i], str, size);

        PLog("\r\nfile done: %s\r\n", files[i]);

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
        D_Doc_Log(ctx_tokenize, doc);
    }
#endif

    // free
    CTX_Tokenize_Free(ctx_tokenize);
    Context_Free(ctx);
    printf("Compile Done!\r\n");
}

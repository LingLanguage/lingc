#include "Compiler.h"

int main(int argc, char **argv) {

    StringCommon_Init();


    // lingc.exe -i ../tests/src
    const string dir = GetWorkingDirectory();
    if (argc < 3) {
        printf("Usage: lingc.exe -i <input directory>\n");
        return 0;
    }

    if (strcmp(argv[1], "-i") != 0) {
        printf("Usage: lingc.exe -i <input directory>\n");
        return 0;
    }

    const string root = TextFormat("%s\\%s", dir, argv[2]);

    Compile(root);

    return 0;
}
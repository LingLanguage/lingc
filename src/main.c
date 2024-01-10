#include "Compiler.h"

int main(int argc, char **argv) {

    StringCommon_Init();

    const string dir = GetWorkingDirectory();
    const string root = TextFormat("%s\\%s\\%s", dir, "tests", "src");

    Compile(root);

    return 0;
}
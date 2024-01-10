#ifndef FILEHELPER_H__
#define FILEHELPER_H__

#include "../Generic/Generic.h"
#include <dirent.h>

// root must be like: "D:\\lingc\\tests"
// extention must be like: ".png"
int File_RecursiveGetFilesByExtension(const char *root, const char *extension, int count, char **files);
long File_ReadAllText(FILE *fp, char **result);

#endif
#ifndef FILEHELPER_H__
#define FILEHELPER_H__

#include "../Generic.h"
#include <dirent.h>
#include <raylib.h>
#include <stdio.h>

// root must be like: "D:\\lingc\\tests"
// extention must be like: ".png"
int File_RecursiveGetFilesByExtension(const char *root, const char *extension,
                                      int count, char **files) {
    DIR *dir;
    struct dirent *dp;
    dir = opendir(root);
    char path[1024];

    if (!dir) {
        return count;
    }

    while ((dp = readdir(dir)) != NULL) {
        // exclude . and ..
        if (strcmp(dp->d_name, ".") == 0 || strcmp(dp->d_name, "..") == 0) {
            continue;
        }

        memset(path, 0, strlen(path));
        strcpy(path, root);
        strcat(path, "/");
        strcat(path, dp->d_name);

        // extension check by .
        char *ext = strrchr(dp->d_name, '.');
        if (ext != NULL && strcmp(ext, extension) == 0) {
            files[count] = (char *)malloc(strlen(path) + 1);
            strcpy(files[count], path);
            strcat(files[count], "\0");
            count++;
        } else {
            count = File_RecursiveGetFilesByExtension(path, extension, count,
                                                      files);
        }
    }

    closedir(dir);

    return count;
}

long File_ReadAllText(FILE *fp, char **result) {

    fseek(fp, 0, SEEK_END);
    long fsize = ftell(fp);

    fseek(fp, 0, SEEK_SET);

    char *str = malloc(fsize + 1);
    for (long i = 0; i < fsize + 1; i++) {
        int c = fgetc(fp);
        if (feof(fp)) {
            str[i] = '\0';
            break;
        }
        str[i] = c;
    }

    *result = str;

    return fsize;
}

#endif
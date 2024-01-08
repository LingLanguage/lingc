#ifndef GENERIC_H__
#define GENERIC_H__

#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <utf8.h>

#include "Enums.h"
#include "Errors.h"
#include "Keywords.h"
#include "Rules.h"

#define string   utf8_int8_t *
#define byte     unsigned char
#define NoneChar '\0'

#define PLogNA(x) printf("%s:%d %s", __FILE__, __LINE__, x)
#define PLog(x, ...)                                                                                                                                           \
    printf("%s:%d ", __FILE__, __LINE__);                                                                                                                      \
    printf(x, __VA_ARGS__)
#define PFailed(file, line, err)                                                                                                                               \
    PLogNA("");                                                                                                                                                \
    printf("%s %s:%d\r\n", err, file, line);                                                                                                                   \
    exit(EXIT_FAILURE)

#endif
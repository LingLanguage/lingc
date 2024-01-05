#ifndef GENERIC_H__
#define GENERIC_H__

#include <utf8.h>

#ifndef bool
#define bool unsigned char
#define true 1
#define false 0
#endif

#define PLogNA(x) printf("%s:%d %s", __FILE__, __LINE__, x)
#define PLog(x, ...) printf("%s:%d ", __FILE__, __LINE__); printf(x, __VA_ARGS__)

#define string utf8_int8_t *
#define byte unsigned char

// ==== Rule ====
const int RULE_FUNCTION_RETURN_MAX = 8;
const int RULE_FUNCTION_PARAM_MAX = 32;

#endif
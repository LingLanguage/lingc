#include "StringCommon.h"

bool String_IsAccess(const string word) {
    int KW_ACCESS_COUNT = sizeof(KW_ACCESS) / sizeof(KW_ACCESS[0]);
    for (int i = 0; i < KW_ACCESS_COUNT; i++) {
        if (String_SameWhenTrimEnd(word, KW_ACCESS[i])) {
            return true;
        }
    }
    return false;
}

bool String_SameWhenTrimEnd(const string a, const string b) {
    int a_len = strlen(a);
    int b_len = strlen(b);
    if (a_len == 0 || b_len == 0) {
        return false;
    }
    int a_index = a_len;
    for (int i = a_len - 1; i >= 0; i--) {
        if (a[i] != KW_SPACE && a[i] != KW_NEWLINE && a[i] != KW_NEWLINE_R && a[i] != KW_TABLE) {
            a_index = i;
            break;
        }
    }
    int b_index = b_len;
    for (int i = b_len - 1; i >= 0; i--) {
        if (b[i] != KW_SPACE && b[i] != KW_NEWLINE && b[i] != KW_NEWLINE_R && b[i] != KW_TABLE) {
            b_index = i;
            break;
        }
    }
    if (a_index != b_index) {
        return false;
    }
    for (int i = 0; i <= a_index; i++) {
        if (a[i] != b[i]) {
            return false;
        }
    }
    return true;
}

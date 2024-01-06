#include "StringCommon.h"

bool Char_NotEmpty(char c) {
    return c != KW_SPACE && c != KW_NEWLINE && c != KW_NEWLINE_R && c != KW_TABLE;
}

bool Char_IsNumber(char c) {
    return c >= '0' && c <= '9';
}

bool Char_IsLetter(char c) {
    return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z');
}

bool Char_IsValidVar(char c) {
    return Char_IsLetter(c) || Char_IsNumber(c) || c == '_';
}

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
        if (Char_NotEmpty(a[i])) {
            a_index = i;
            break;
        }
    }
    int b_index = b_len;
    for (int i = b_len - 1; i >= 0; i--) {
        if (Char_NotEmpty(b[i])) {
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

void SwapMaxToLeft(int *left, int *right) {
    if (*left < *right) {
        int temp = *left;
        *left = *right;
        *right = temp;
    }
}
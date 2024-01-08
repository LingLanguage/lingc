#ifndef STRINGCOMMON_H__
#define STRINGCOMMON_H__

#include "Generic.h"

void StringCommon_Init();
const string String_ValidAccess(const string access);
int String_OP_Assign(const string file, int line, int eqIndex, const string code, char *out);
int String_OP_Calc(const char cur, const string file, int line, int eqIndex, const string code, char *out);
int String_OP_CalcOrCommaOrMember(const char cur, const string file, int line, int eqIndex, const string code, char *out);
bool String_IsAccess(const string word);
char Char_IsBracket(char c);
char Char_IsQuote(char c);
char Char_IsEmptySymbol(char c);
char Char_IsSplitSymbol(char c);
char Char_IsLetter(char c);
char Char_IsLetterOrUnderline(char c);
char Char_IsNumber(char c);
char Char_IsLetterOrNumber(char c);
char Char_IsLetterOrNumberOrUnderline(char c);
bool Char_NotEmpty(char c);
bool Char_IsValidVar(char c);

#endif
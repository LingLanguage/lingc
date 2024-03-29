#ifndef STRINGCOMMON_H__
#define STRINGCOMMON_H__

#include "Generic.h"

void StringCommon_Init();
bool OP_Type_IsAssign(OP_Type type);
const string String_ValidAccess(const string access);
void String_CopyAccess(char *dest, const string access);
int String_OP_Assign(const string file, int line, int eqIndex, const string code, char *out);
int String_OP_Calc(const char cur, const string file, int line, int eqIndex, const string code, char *out);
int String_OP_CalcOrCommaOrMember(const char cur, const string file, int line, int eqIndex, const string code, char *out);
const string String_SubString(const string word, int start_index, int end_index);
int String_CutBetweenSameChars(int start_index, const string word, long size, char same_area);
int String_CutBetweenDifferentChars(int start_index, const string word, long size, char left, char right);
bool String_IsAccess(const string word);
bool Char_IsIgnoreAssignPrev(char c);
char Char_IsBracket(char c);
char Char_IsQuote(char c);
char Char_IsEmptySymbolButNewLine(char c);
char Char_IsSplitSymbol(char c);
char Char_IsLetter(char c);
char Char_IsLetterOrUnderline(char c);
char Char_IsNumber(char c);
char Char_IsLetterOrNumber(char c);
char Char_IsLetterOrNumberOrUnderline(char c);
bool Char_NotEmpty(char c);
bool Char_IsValidVar(char c);

#endif
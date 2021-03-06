#pragma once

char *utf8_dec(const char *string, const char *current);
char *utf8_chr(const char *s, const char *sfc);
int utf8_symbol_len(char c);
const char* utf8_inc(const char* string);
char* utf8_inc(char* string);
const char* utf8_pbrk(const char* s, const char* set);
size_t utf8_length(const char *string);
bool utf8_is_lead(char c);
bool utf8_is_cont(char c);

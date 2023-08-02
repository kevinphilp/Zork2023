#ifndef KPUTILS_H
#define KPUTILS_H

#include <stdbool.h>

int strcicmp(char const *a, char const *b);
void hello(void);
size_t strlcpy(char* dst, const char* src, size_t bufsize);
size_t strlcat(char* dst, const char* src, size_t siz);
char *strsep(char **stringp, const char *delim);
char *strdup (const char *s);

#endif

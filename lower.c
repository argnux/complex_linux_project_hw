#include <ctype.h>

#include "convert.h"

void lower(char *text) {
    char *s = text;
    while (*s != '\0') {
        *s = tolower((unsigned char) *s);
        s++;
    }
}


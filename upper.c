#include <ctype.h>

#include "convert.h"

void upper(char *text, Error *) {
    char *s = text;
    while (*s != '\0') {
        *s = toupper((unsigned char) *s);
        s++;
    }
}


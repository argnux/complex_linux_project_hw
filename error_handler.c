#include <stdio.h>

#include "error_handler.h"

void set_error(Error *err, const char *what) {
    err->what = (char*)what;
    err->is_set = 1;
}

void unset_error(Error *err) {
    err->what = NULL;
    err->is_set = 0;
}

void print_error(Error *err) {
    fprintf(stderr, "Error: %s\n", err->what);
}

void print_and_unset_error(Error *err) {
    print_error(err);
    unset_error(err);
}


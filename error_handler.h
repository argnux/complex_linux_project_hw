#ifndef ERROR_HANDLER
#define ERROR_HANDLER

typedef struct {
    int is_set;
    char *what;
} Error;

void set_error(Error *err, const char *what);
void unset_error(Error *err);
void print_error(Error *err);
void print_and_unset_error(Error *err);

#endif


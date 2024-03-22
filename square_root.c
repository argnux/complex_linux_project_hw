#include <math.h>

#include "calc.h"

double square_root(double num, Error *err) {
    if (num >= 0) {
        return sqrt(num);
    }

    set_error(err, "Square root from negative number!");
    return 0;
}


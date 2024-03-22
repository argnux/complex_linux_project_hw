#include "calc.h"

double fraction(double a, double b, Error *err) {
    if (b != 0) {
        return a / b;
    }

    set_error(err, "Division by zero!");
    return 0;
}


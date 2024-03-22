#include "calc.h"

double factorial(double num, Error *) {
    if (num > 0) {
        return num * factorial(num - 1, 0);
    } else {
        return 1;
    }
}


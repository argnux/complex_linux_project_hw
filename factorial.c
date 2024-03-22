#include "calc.h"

double factorial(double num) {
    if (num > 0) {
        return num * factorial(num - 1);
    } else {
        return 1;
    }
}


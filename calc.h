#ifndef CALC_H
#define CALC_H

#include "error_handler.h"

double sum(double, double, Error *);
double difference(double, double, Error *);
double product(double, double, Error *);
double fraction(double, double, Error *);

double factorial(double, Error *);
double square_root(double, Error *);

#endif


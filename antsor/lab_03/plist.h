#ifndef PLIST_H
#define PLIST_H

#include "array.h"
#include "matrix.h"

double func(double x, double y);

void make_plist(Array *xarr, Array *yarr, Matrix *zmatr,
                double x, double y, double hx, double hy);

void print_plist(Array *xarr, Array *yarr, Matrix *zmatr);

void write_plist(FILE *f, Array *xarr, Array *yarr, Matrix *zmatr);

#endif
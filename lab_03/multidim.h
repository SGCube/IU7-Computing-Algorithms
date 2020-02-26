#ifndef MULTIDIM_H
#define MULTIDIM_H

#include "array.h"
#include "matrix.h"

double multidim_interpol(Array *xarr, Array *yarr, Matrix *zmatr,
                            double x, double y, int nx, int ny);

#endif
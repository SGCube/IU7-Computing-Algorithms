#include <assert.h>
#include "multidim.h"
#include "interpol.h"

double multidim_interpol(Array *xarr, Array *yarr, Matrix *zmatr,
                            double x, double y, int nx, int ny)
{
    assert(xarr && yarr && zmatr);
    
    double *zy = new double[xarr->size];
    assert(zy);

    for (int i = 0; i < xarr->size; i++)
        zy[i] = solve(yarr->arr, zmatr->matr[i], y, ny, yarr->size);
    double z = solve(xarr->arr, zy, x, nx, xarr->size);

    delete [] zy;
    return z;
}
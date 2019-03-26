#include <assert.h>
#include "multidim.h"

double multidim_interpol(Array *xarr, Array *yarr, Matrix *zmatr,
                            double x, double y)
{
    assert(xarr && yarr && zmatr);

    double *zy = new double[xarr->size];
    assert(zy);

    for (int i = 0; i < xarr->size; i++)
    {
        
    }
}
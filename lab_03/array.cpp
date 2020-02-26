#include <assert.h>

#include "array.h"

Array::Array()
{
    arr = nullptr;
    size = 0;
}

Array::Array(int n)
{
    arr = new double[n];
    if (!arr)
        return;
    size = n;
}

Array::~Array()
{
    delete [] arr;
}

void Array::read(FILE *f)
{
    assert(f);

    if (fscanf(f, "%d", &size) != 1 || size < 1)
    {
        size = 0;
        return;
    }

    arr = new double[size];
    if (!arr)
    {
        size = 0;
        return;
    }
    
    for (int i = 0; i < size; i++)
        if (fscanf(f, "%lf", &arr[i]) != 1)
        {
            clear();
            return;
        }
}

void Array::print()
{
    for (int i = 0; i < size; i++)
        printf("%lf ", arr[i]);
    printf("\n");
}

void Array::clear()
{
    delete [] arr;
    arr = nullptr;
    size = 0;
}
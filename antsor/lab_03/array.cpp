#include "array.h"

double *read_array(FILE *f, int *n)
{
    if (!f || !n)
        return nullptr;
    
    int k = 0;
    if (fscanf(f, "%d", &k) != 1 || k < 1)
        return nullptr;

    double *arr = new double[k];
    if (!arr)
        return nullptr;
    
    for (int i = 0; i < k; i++)
        if (fscanf(f, "%lf", &arr[i]) != 1)
        {
            free(arr);
            return nullptr;
        }

    *n = k;
    return arr;
}

void print_array(double *arr, int n)
{
    for (int i = 0; i < n; i++)
        printf("%lf ", arr[i]);
    printf("\n");
}
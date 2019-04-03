#include <stdio.h>
#include "multidim.h"

double func(double x, double y)
{
	return x * x + y * y;
}

void make_plist(Array *xarr, Array *yarr, Matrix *zmatr,
                double x, double y, double hx, double hy)
{
    xarr->arr[0] = x;
    for (int i = 1; i < xarr->size; i++)
        xarr->arr[i] = xarr->arr[i - 1] + hx;
    
    yarr->arr[0] = y;
    for (int i = 1; i < yarr->size; i++)
        yarr->arr[i] = yarr->arr[i - 1] + hy;

    for (int i = 0; i < xarr->size; i++)
        for (int j = 0; j < yarr->size; j++)
            zmatr->matr[i][j] = func(xarr->arr[i], yarr->arr[j]);
}

void print_plist(Array *xarr, Array *yarr, Matrix *zmatr)
{
    printf("%8s│", " ");
    for (int i = 0; i < yarr->size; i++)
        printf("%8.4lf ", yarr->arr[i]);
    printf("\n────────┼");
    for (int i = 0; i < yarr->size; i++)
        printf("─────────");
    printf("▶ y\n");
    for (int i = 0; i < xarr->size; i++)
    {
        printf("%-8.4lf│", xarr->arr[i]);
        for (int j = 0; j < yarr->size; j++)
            printf("%8.4lf ", zmatr->matr[i][j]);
        printf("\n");
    }
    printf("%8s▼\n%8sx\n", " ", " ");
}

void write_plist(FILE *f, Array *xarr, Array *yarr, Matrix *zmatr)
{
    fprintf(f, "%d\n", xarr->size);
    for (int i = 0; i < xarr->size; i++)
        fprintf(f, "%lf ", xarr->arr[i]);
    fprintf(f, "\n%d\n", yarr->size);
    for (int i = 0; i < yarr->size; i++)
        fprintf(f, "%lf ", yarr->arr[i]);
    fprintf(f, "\n");
    for (int i = 0; i < xarr->size; i++)
    {
        for (int j = 0; j < yarr->size; j++)
            fprintf(f, "%lf ", zmatr->matr[i][j]);
        fprintf(f, "\n");
    }
}

#include <stdio.h>
#include <stdlib.h>
#include "matrix.h"
#include <QDebug>

#define OK 0
#define WR_ELEM -4
#define ERR_MALLOC 5
#define NOT_EN 6
#define NO_MAT 7

double **allocate_matrix(int n, int m)
{
    double **matrix = NULL;
    matrix = (double **)malloc(n * sizeof(double *));
    if (!matrix)
        return NULL;
    double *data = NULL;
    data = (double *)calloc(n * m, sizeof(double));
    if (!data)
    {
        free(matrix);
        return NULL;
    }
    for (int i = 0; i < n; i++)
        matrix[i] = data + i * m;
    return matrix;
}

int read_matrix(double ***matrix, int n, FILE *f)
{
    double rc = 0;
    int kol = 0;

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            rc = fscanf(f, "%lf", &(*matrix)[i][j]);
            if (rc != 1 && rc != EOF)
                return WR_ELEM;
            else if (rc == 1)
                kol++;
        }
    }
    if (kol == 0)
        return NO_MAT;
    else if (kol < n * 3)
        return NOT_EN;
    return OK;
}

void free_matrix(double **matrix)
{
    delete matrix[0];
    delete matrix;
}

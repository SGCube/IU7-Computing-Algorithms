#include <stdio.h>
#include <stdlib.h>
#include "func.h"
#include "matrix.h"
#include <math.h>
#include <QDebug>

#define WR_AM 3
#define EMPTY 2
#define ERR 1
#define OK 0
#define ERR_MALLOC -3
#define WR_ELEM -4
#define NOT_EN 6
#define NO_SUCH -7

int read_from_file(FILE *f, int *amount, double ***matrix)
{
    int rc;

    rc = fscanf(f, "%d", amount);
    if (rc == EOF)
        return EMPTY;
    if (rc != 1 || *amount <= 0)
        return WR_AM;
    *matrix = allocate_matrix(*amount, 3);
    if (!*matrix)
        return ERR_MALLOC;
    rc = read_matrix(matrix, *amount, f);
    if (rc != OK)
        return rc;
    return OK;
}

double F(double x, int k)
{
    return pow(x, k);
}


double **get_slau_matrix(double **table, int amount, int n, double **col)
{
    double **matrix = allocate_matrix(n + 1, n + 1);
    if (!matrix)
        return NULL;
    for (int m = 0; m < n + 1; m++)
    {
        for (int i = 0; i < amount; i++)
        {
            double tmp = table[i][2] * F(table[i][0], m);
            for (int k = 0; k < n + 1; k++)
                matrix[m][k] += tmp * F(table[i][0], k);
            (*col)[m] += tmp * table[i][1];
        }
    }
    return matrix;
}

// Обмен строк в матрице
void swap_lines(double **matrix, double **id, int n, int i, int j)
{
    double temp;
    for (int k = 0; k < n; k++)
    {
        temp = matrix[i][k];
        matrix[i][k] = matrix[j][k];
        matrix[j][k] = temp;

        temp = id[i][k];
        id[i][k] = id[j][k];
        id[j][k] = temp;
    }
}

// Поставить на место row строку с наибольшим ведущим коэффициентом
void pivotize(double **matrix, double **id, int n, int row)
{
    int max_index = row;
    double max_value = fabs(matrix[row][row]);
    double current_value;
    for (int i = row + 1; i < n; i++)
    {
        current_value = fabs(matrix[i][row]);
        if (current_value > max_value)
        {
            max_index = i;
            max_value = current_value;
        }
    }

    if (row != max_index)
        swap_lines(matrix, id, n, row, max_index);
}

// Разделить строку матрицы на значение
void devide(double **matrix, int n, int i, double denominator)
{
    for (int j = 0; j < n; j++)
    matrix[i][j] /= denominator;
}

// Обнуление элементов под ведущим элементом в строке x
void subtract_below(double **matrix, double **id, int n, int x)
{
    double koeff;
    for (int i = x + 1; i < n; i++)
    {
        koeff = matrix[i][x] / matrix[x][x];
        for (int j = x; j < n; j++)
            matrix[i][j] -= koeff * matrix[x][j];
        for (int j = 0; j < n; j++)
            id[i][j] -= koeff * id[x][j];
    }
}

// Обнуление элементов над ведущим элементом в строке x
void subtract_above(double **matrix, double **id, int n, int x)
{
    double koeff;
    for (int i = x - 1; i >= 0; i--)
    {
        koeff = matrix[i][x] / matrix[x][x];
        for (int j = x; j >= 0; j--)
            matrix[i][j] -= koeff * matrix[x][j];
        for (int j = 0; j < n; j++)
            id[i][j] -= koeff * id[x][j];
    }
}

// Обращение матрицы методом Гаусса-Жордана
void inverse(double **matrix, double **id, int n)
{
    // Прямой ход
    for (int i = 0; i < n - 1; i++)
    {
        // Обмен строк
        pivotize(matrix, id, n, i);

        // Обнулить элементы ниже ведущего
        subtract_below(matrix, id, n, i);
    }

    // Обратный ход
    for (int i = n - 1; i > 0; i--)// Обнулить элементы выше ведущего
    subtract_above(matrix, id, n, i);

    // Разделить строки на ведущие элементы
    for (int i = 0; i < n; i++)
    {
        devide(id, n, i, matrix[i][i]);
        devide(matrix, n, i, matrix[i][i]);
    }
}

double **solve(double **matrix, int amount, int m)
{
    int n = m + 1;
    double **id = allocate_matrix(n, n);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
          id[i][j] = i == j ? 1.0 : 0.0;
        }
      }
      inverse(matrix, id, n);
      return id;
}

double *mult(double **mat_a, double *col, int am)
{
    double *c = (double *)calloc(am, sizeof(double));
    for (int j = 0; j < am; j++)
    {
        for (int k = 0; k < am; k++)
            c[j] += col[k] * mat_a[j][k];
    }
    return c;
}

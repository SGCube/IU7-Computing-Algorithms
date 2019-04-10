#include <cmath>
#include "matrixsolve.h"
#include "func.h"
#include "matrix.h"

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
void divide(double **matrix, int n, int i, double denominator)
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
        divide(id, n, i, matrix[i][i]);
        divide(matrix, n, i, matrix[i][i]);
    }
}

double **solve(double **matrix, int n)
{
    double **id = calloc_matrix(n + 1, n + 1);
	if (!id)
		return NULL;
	
    for (int i = 0; i < n + 1; i++)
		for (int j = 0; j < n + 1; j++)
			id[i][j] = i == j ? 1 : 0;
	inverse(matrix, id, n + 1);
	
	return id;
}

double *multiply(double **matrix, double *column, int n)
{
    double *res = (double *)calloc(n, sizeof(double));
	if (!res)
		return NULL;
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            res[i] += matrix[i][j] * column[j];
    return res;
}

double **sle_matrix(double **plist, int size, int n, double **col)
{
    double **matrix = calloc_matrix(n + 1, n + 1);
    if (!matrix)
        return NULL;
	
	*col = (double *) calloc(n + 1, sizeof(double));
    if (!*col)
	{
		clear_matrix(matrix, n + 1);
        return NULL;
	}
	
    for (int m = 0; m < n + 1; m++)
    {
        for (int i = 0; i < size; i++)
        {
            double t = plist[i][2] * f(plist[i][0], m);
            for (int k = 0; k < n + 1; k++)
                matrix[m][k] += t * f(plist[i][0], k);
            (*col)[m] += t * plist[i][1];
        }
    }
    return matrix;
}

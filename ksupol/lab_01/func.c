#include <stdio.h>
#include "func.h"
#include "matrix.h"
#include <math.h>

#define OK 0
#define WR_ELEM -4
#define EMPTY 2
#define WR_AM 3
#define ERR_MALLOC 5
#define NOT_EN 6
#define NO_MAT 7

double f(double x)
{
	return sin(x + 90);
}

int read_from_file(FILE *f, int *amount, double ***matrix)
{
	int rc;
	
	rc = fscanf(f, "%d", amount);
	if (rc == EOF)
		return EMPTY;
	if (rc != 1 || *amount <= 0)
		return WR_AM;
	*matrix = allocate_matrix(*amount, 2);
	if (!*matrix)
		return ERR_MALLOC;
	rc = read_matrix(matrix, *amount, f);
	if (rc != OK)
		return rc;
	return OK;
}

void sort(int n, double **matrix)
{
	double *tmp = NULL;
	for (int i = 1; i < n; i++)
	{
        for (int j = 1; j < n; j++)
		{
            if (matrix[j][0] < matrix[j-1][0])
			{
                tmp = matrix[j];
                matrix[j] = matrix[j-1];
                matrix[j-1] = tmp;
            }
        }
	}
}

int find_interval(int n, int a, double **matrix, double x, 
		int *up, int *down)
{
	if (x < matrix[0][0])
	{
		*up = 0;
		*down = n;
		return -1;
	}
	if (x > matrix[a-1][0])
	{
		*up = a - n - 1;
		*down = a - 1;
		return -2;
	}
	if (a - 1 == n)
	{
		*up = 0;
		*down = a - 1;
		return OK;
	}
	int ii = 0;
	for (int i = 0; i < a - 1; i++)
	{
		if (x >= matrix[i+1][0])
			ii++;
		else
			break;
	}
	//если кол-во узлов четное
	if ((n + 1) % 2 == 0)
	{
		if (ii - (n + 1)/2 >= 0 && ii + (n + 1)/2 <= a - 1)
		{
			*up = ii - (n + 1)/2 + 1;
			*down = ii + (n + 1)/2;
		}
		if (ii - (n + 1)/2 < 0)
		{
			*up = 0;
			*down = n;
		}
		if (ii + (n + 1)/2 > a)
		{
			*up = ii - n;
			*down = a - 1;
		}
	}
	//если кол-во узлов нечетное
	else
	{
		if (ii - n / 2 >= 0 && ii + n / 2 <= a - 1)
		{
			*up = ii - n / 2;
			*down = ii + n / 2;
		}
		if (ii - n / 2 < 0)
		{
			*up = 0;
			*down = n;
		}
		if (ii + n/2 > a - 1)
		{
			*up = ii - n;
			*down = a - 1;
		}
	}
	return OK;
}

double **diff(double **matrix, int up, int down, int n)
{
	double **result;
	result = allocate_matrix(n + 1, n + 1);
	if (!*result)
		return NULL;
	int k = 0;
	for (int i = up; i < down + 1; i++)
	{
		result[k][0] = matrix[i][1];
		k++;
	}
	
	for (int i = 1; i < n + 1; i++)
	{
        for (int j = 0; j < n + 1 - i; j++)
		{
            result[j][i] = (result[j][i - 1] - result[j + 1][i - 1]) /
                    (matrix[j][0] - matrix[j + i][0]);
		}
	}
	print_matrix(result, n+1, n+1);
	return result;
}

void interpolate(double **result, int n, double x, double **matrix,
				int up, int down)
{
	double res = result[0][0];
    double a = 1;
    for (int i = 1; i < n + 1; i++)
    {
        a *= x - matrix[up + i - 1][0];
        res += a * result[0][i];
    }
	printf("Result: y(%lf) = %lf\n", x, res);
	printf("True result: y(%lf) = %lf\n", x, f(x));
}
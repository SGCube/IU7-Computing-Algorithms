#ifndef __SPLINE__H__
#define __SPLINE__H__

//функция чтения из файла
int read_from_file(FILE *f, int *amount, double ***matrix);

//функция сортировки
void sort(int n, double **matrix);

//функция нахождения коэффициентов
double **create_table_koeff(double **matrix, int n);

//
double **create_table_c(double **matrix, int n);

double *create_f(double **matrix, int n);

double *find_c_koeff(double **c, double *f, int n);

void fill_table_koeff(double **m, double **koeff, double *c_koeff, int n);

int find_interval(double x, int *from, int *to, double **matrix, int n);

float find_y(int from, int to, double x, double **koeff, double **matr);

#endif
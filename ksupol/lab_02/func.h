#ifndef __FUNC__H__
#define __FUNC__H__

//функция чтения из файла
int read_from_file(FILE *f, int *amount, double ***matrix);

//функция сортировки
void sort(int n, double **matrix);

//функция нахождения коэффициентов
double **create_table_koeff(double **matrix, int n);

#endif
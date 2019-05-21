#ifndef __FUNC__H__
#define __FUNC__H__

//функция чтения из файла
int read_from_file(FILE *f, int *amount, double ***matrix);

void one_side(int amount, double **matrix);

void increased_accuracy(int amount, double **matrix);

//функция подсчета точного результата
void real(int amount, double **matrix);
#endif
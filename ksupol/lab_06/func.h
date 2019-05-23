#ifndef __FUNC__H__
#define __FUNC__H__

//функция чтения из файла
int read_from_file(FILE *f, int *amount, double ***matrix);

void one_side(int amount, double **matrix);

void increased_accuracy(int amount, double **matrix);

void central(int am, double **matrix);
void centrall(int am, double **m);

void runge(int am, double **matrix);

void align(int am, double **matrix);

//функция подсчета точного результата
void real(int amount, double **matrix);


double ksi(double x);
double eta_from_ksi();
double eta(double y);
#endif
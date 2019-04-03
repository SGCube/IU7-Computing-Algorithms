#ifndef __FUNC__H__
#define __FUNC__H__

//функция чтения из файла
int read_from_file(FILE *f, int *am_x, int *am_y, double ***matrix);

//функция сортировки матрицы
void sort(int n, double **matrix, int k);

int create_x_y(double **matrix, int am_x, int am_y, double **m_x,
				double **m_y, double ***m_z);

double **differ(double *m_z, double *m_y, int up, int down, int n);
				
//функция нахождения интервала
int find_interval(int n, int a, double *matrix, double x, 
		int *up, int *down);
		
double **diff(double **m_z, double *m_x, int up, int down, 
			int n, int p);

double interpolate(double **result, int n, double x, double *m_x, 
				int up);
				
double interpolate2(double **result, int n, double x, double *m_x, 
				int up);
#endif
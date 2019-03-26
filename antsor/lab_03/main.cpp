#include <stdio.h>

int main(int argc, char **argv)
{
	if (argc < 2)
	{
		printf("Нет входного файла!\n");
		return 0;
	}
	
	FILE *f = fopen(argv[1], "r");
	if (!f)
	{
		printf("Ошибка открытия файла!\n");
		return 0;
	}

	double kx = 0;
	double *xarr = read_array(f, &kx);
	if (!xarr)
	{
		printf("Ошибка чтения файла (массив x)!\n");
		fclose(f);
		return 0;
	}

	double ky = 0;
	double *yarr = read_array(f, &ky);
	if (!yarr)
	{
		printf("Ошибка чтения файла (массив y)!\n");
		free(xarr);
		fclose(f);
		return 0;
	}

	double **zmatr = read_matrix(f, kx, ky);
	if (!zmatr)
	{
		printf("Ошибка чтения файла (матрица z)!\n");
		free(xarr);
		free(yarr);
		fclose(f);
		return 0;
	}
	fclose(f);

	printf("Введите x и y: ");
	double x, y;
	if (scanf("%lf%lf", &x, &y) != 2)
	{
		printf("Некорректные данные!\n");
		free(xarr);
		free(yarr);
		free_matrix(zmatr);
	}

	return 0;
}

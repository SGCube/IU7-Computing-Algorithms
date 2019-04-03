#include <stdio.h>

#include "array.h"
#include "matrix.h"
#include "multidim.h"
#include "plist.h"

int main(int argc, char **argv)
{
	setbuf(stdout, NULL);
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
	
	Array xarr = Array(), yarr = Array();
	xarr.read(f);
	if (!xarr.arr)
	{
		printf("Ошибка чтения файла (массив x)!\n");
		fclose(f);
		return 0;
	}

	yarr.read(f);
	if (!yarr.arr)
	{
		printf("Ошибка чтения файла (массив y)!\n");
		delete &xarr;
		fclose(f);
		return 0;
	}
	
	Matrix zmatr = Matrix();
	zmatr.read(f, xarr.size, yarr.size);
	if (!zmatr.matr)
	{
		printf("Ошибка чтения файла (матрица z)!\n");
		delete &xarr;
		delete &yarr;
		fclose(f);
		return 0;
	}
	fclose(f);

	print_plist(&xarr, &yarr, &zmatr);

	printf("Введите x и y: ");
	double x, y;
	if (scanf("%lf%lf", &x, &y) != 2)
	{
		printf("Некорректные данные!\n");
		delete &xarr;
		delete &yarr;
		delete &zmatr;
		return 0;
	}

	printf("Введите степени полинома nx и ny: ");
	int nx, ny;
	if (scanf("%d%d", &nx, &ny) != 2 || nx >= xarr.size || ny >= yarr.size)
	{
		printf("Некорректные данные!\n");
		delete &xarr;
		delete &yarr;
		delete &zmatr;
		return 0;
	}

	double z = multidim_interpol(&xarr, &yarr, &zmatr, x, y, nx, ny);
	printf("\nz(%lf; %lf) = %lf\n", x, y, z);

	delete &xarr;
	delete &yarr;
	delete &zmatr;

	return 0;
}

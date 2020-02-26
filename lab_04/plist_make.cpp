#include <stdio.h>
#include <stdlib.h>
#include <time.h>

double func(double x)
{
	return x * x * x;
}

void file_func(char *fname, double a, double b, int n)
{
	FILE *f = fopen(fname, "w");
	if (!f)
		return;
	
	fprintf(f, "%d\n", n);
	
	double x, y;
	
	for (int i = 0; i < n; i++)
	{
		x = (double)rand() / RAND_MAX * (b - a) + a;
		y = (double)rand() / RAND_MAX * (b - a) + a;
		fprintf(f, "%lf\t%lf\t%d\n", x, y, 1);
	}
	
	fclose(f);
}

void file_func2(char *fname, double a, double b, double h)
{
	if (h != 0)
	{
		FILE *f = fopen("data.txt", "w");
		if (!f)
			return;
		
		int n = (b - a) / h + 1;
		fprintf(f, "%d\n", n);
		
		while (a <= b)
		{
			fprintf(f, "%lf\t%lf\t%d\n", a, func(a), 1);
			a += h;
		}
		
		fclose(f);
	}
}

int main(int argc, char **argv)
{
    setbuf(stdout, NULL);
	srand(time(NULL));
    if (argc < 2)
    {
        printf("Не указан входной файл!\n");
        return 0;
    }

    double x1, x2;
    printf("Введите диапазон: ");
    if (scanf("%lf%lf", &x1, &x2) != 2)
    {
        printf("Некорректные данные!\n");
        return 0;
    }
	
	/*int nx;
    printf("Введите количество: ");
    if (scanf("%d", &nx) != 1)
    {
        printf("Некорректные данные!\n");
        return 0;
    }

    file_func(argv[1], x1, x2, nx);*/

    double dx;
    printf("Введите шаг: ");
    if (scanf("%lf", &dx) != 1)
    {
        printf("Некорректные данные!\n");
        return 0;
    }

    file_func2(argv[1], x1, x2, dx);

    return 0;
}
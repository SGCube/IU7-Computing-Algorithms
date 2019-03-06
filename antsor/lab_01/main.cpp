#include <stdio.h>

#include "interpol.h"
#include "matrix.h"
#include "error.h"
#include "func.h"

int main(int argc, char *argv[])
{
	setbuf(stdout, NULL);
	FILE *fin = NULL;
	if (argc < 2)
	{
		file_func(-2, 2, 10);
		fin = fopen("data.txt", "r");
		if (!fin)
		{
			printf("Can't open file!\n");
			return 0;
		}
	}
	else
	{
		fin = fopen(argv[1], "r");
		if (!fin)
		{
			printf("Can't open file!\n");
			return 0;
		}

	}
	int k = 0;
	double x = 0;
	int n = 0;
	double **plist = read_matrix(fin, &k);
	if (!plist)
	{
		printf("Data read error!\n");
		fclose(fin);
		return 0;
	}
	printf("y(x) = cos(x) - x");
	printf("\nX\t|Y\t\n");
	print_matrix(plist, k);
	printf("\n");
	
	printf("Enter x and n: ");
	if (scanf("%lf%d", &x, &n) != 2 || n < 1)
	{
		printf("Read error!\n");
		fclose(fin);
		clear_matrix(plist, k);
		return 0;
	}
	
	printf("\nY(%lf)\t= %lf\n", x, solve(plist, x, n, k));
	printf("func(%lf)\t= %lf\n", x, func(x));
	
	fclose(fin);
	clear_matrix(plist, k);
    return 0;
}

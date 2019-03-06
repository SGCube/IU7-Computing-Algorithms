#include <stdio.h>

#include "interpol.h"
#include "matrix.h"
#include "error.h"
#include "func.h"

int main(int argc, char *argv[])
{
	FILE *fin = NULL;
	
	if (argc < 2)
	{
		file_func(-2, 2, 10);
		fin = fopen("data.txt", "r");
		if (!fin)
			printf("Can't open file!\n");
		return 0;
	}
	else
	{
		fin = fopen(argv[1], "r");
		if (!fin)
			printf("Can't open file!\n");
		return 0;
	}
	
	int k = 0;
	double x = 0;
	int n = 0;
	double **plist = read_matrix(f, &k);
	if (!plist)
	{
		printf("Data read error!\n");
		fclose(fin);
		return 0;
	}
	
	printf("Enter x and n: ");
	if (scanf("%lf%d") != 2 || n < 1)
	{
		printf("Read error!\n");
		fclose(fin);
		clear_matrix(plist, k);
		return 0;
	}
	
	printf("\nY(%lf) = %lf\n", x, solve(plist, x, n, k));
	printf("func(%lf) = %lf\n", x, func(x));
	
	clear_matrix(plist, k);
    return 0;
}

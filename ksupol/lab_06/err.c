#include <stdio.h>
#include "err.h"

void err_code(int rc)
{
	if (rc == EMPTY)
		printf("File is empty!\n");
	else if (rc == WR_AM)
		printf("Amount of rows is wrong!\n");
	else if (rc == NOT_EN)
		printf("Not enough elements in matrix!\n");
	else if (rc == NO_MAT)
		printf("There is no matrix!\n");
	else if (rc == WR_ELEM)
		printf("Element of matrix is wrong!\n");
}
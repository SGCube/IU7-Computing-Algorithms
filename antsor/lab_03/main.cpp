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
	}


	fclose(f);

	return 0;
}

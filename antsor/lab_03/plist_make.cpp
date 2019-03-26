#include <stdio.h>

#include "plist.h"

int main(int argc, char **argv)
{
    setbuf(stdout, NULL);
    if (argc < 2)
    {
        printf("Не указан входной файл!\n");
        return 0;
    }

    double x, y;
    printf("Введите начальную точку: ");
    if (scanf("%lf%lf", &x, &y) != 2)
    {
        printf("Некорректные данные!\n");
        return 0;
    }

    double hx, hy;
    printf("Введите шаги по x и y: ");
    if (scanf("%lf%lf", &hx, &hy) != 2)
    {
        printf("Некорректные данные!\n");
        return 0;
    }

    int nx, ny;
    printf("Введите кол-во точек по x и y: ");
    if (scanf("%d%d", &nx, &ny) != 2)
    {
        printf("Некорректные данные!\n");
        return 0;
    }

    Array xarr = Array(nx);
    Array yarr = Array(ny);
    Matrix zmatr = Matrix(nx, ny);

    if (!xarr.arr || !yarr.arr || !zmatr.matr)
    {
        printf("Ошибка выделения памяти!\n");
        if (xarr.arr)
            delete &xarr;
        if (yarr.arr)
            delete &yarr;
        if (zmatr.matr)
            delete &zmatr;
        return 0;
    }

    make_plist(&xarr, &yarr, &zmatr, x, y, hx, hy);

    FILE *f = fopen(argv[1], "w");
    if (!f)
        printf("Ошибка открытия/создания файла!\n");
    else
    {
        write_plist(f, &xarr, &yarr, &zmatr);
        print_plist(&xarr, &yarr, &zmatr);
    }
    
    delete &xarr;
    delete &yarr;
    delete &zmatr;

    return 0;
}
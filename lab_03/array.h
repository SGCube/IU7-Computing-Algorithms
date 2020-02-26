#ifndef ARRAY_H
#define ARRAY_H

#include <stdio.h>

struct Array
{
    double *arr;
    int size;

    Array();
    Array(int n);
    ~Array();

    void read(FILE *f);
    void print();
    void clear();
};

#endif
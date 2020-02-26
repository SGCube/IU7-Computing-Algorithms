#ifndef VECTOR_H
#define VECTOR_H

#include <QVector>
#include "qcustomplot.h"

#define PLOT_N 100

template <typename T>
T vector_max(QVector<T> v);

template <typename T>
T vector_min(QVector<T> v);

void draw_plot(QCustomPlot *plot, double **plist, int plist_size,
			   double *cres, double n);

#endif // VECTOR_H

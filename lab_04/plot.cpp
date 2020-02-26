#include "qcustomplot.h"
#include "plot.h"
#include "func.h"

template <typename T>
T vector_max(QVector<T> v)
{
    T vmax = v[0];
    for (int i = 0; i < v.size(); i++)
        if (v[i] > vmax)
			vmax = v[i];
    return vmax;
}

template <typename T>
T vector_min(QVector<T> v)
{
	T vmin = v[0];
    for (int i = 0; i < v.size(); i++)
        if (v[i] < vmin)
			vmin = v[i];
    return vmin;
}

void draw_plot(QCustomPlot *plot, double **plist, int plist_size,
			   double *cres, double n)
{
	QVector<double> table_x(plist_size), table_y(plist_size);
    for (int i = 0; i < plist_size; i++)
    {
        table_x[i] = plist[i][0];
        table_y[i] = plist[i][1];
    }
	
    QVector<double> plot_x(PLOT_N + 1), plot_y(PLOT_N + 1);
    
    double xfirst = plist[0][0], xlast = plist[plist_size - 1][0];
	double x = xfirst, y = 0;
	double dx = (xlast - xfirst) / PLOT_N;
	
    for (int i = 0; i < PLOT_N + 1; i++, x += dx)
	{
        plot_x[i] = x;
		
		y = 0;
        for (int j = 0; j < n + 1; j++)
            y += f(x, j) * cres[j];
        plot_y[i] = y;
	}
	
	double ymin = vector_min(plot_y);
	double ymax = vector_max(plot_y);
	
	double ytmin = vector_min(table_y);
	double ytmax = vector_max(table_y);
	
	ymin = fmin(ymin, ytmin);
	ymax = fmax(ymax, ytmax);
	
    plot->clearGraphs();
	
	plot->xAxis->setLabel("x");
    plot->yAxis->setLabel("y");
    plot->xAxis->setRange(xfirst - 1, xlast + 1);
    plot->yAxis->setRange(ymin - 1, ymax + 1);
	
    plot->addGraph()->setData(table_x, table_y);
    plot->graph(0)->setPen(QColor(255, 0, 0));
    plot->graph(0)->setLineStyle(QCPGraph::lsNone);
    plot->graph(0)->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssDisc, 4));
	
    plot->addGraph()->setData(plot_x, plot_y);
	plot->graph(1)->setPen(QColor(0, 0, 255));

    plot->replot();
}

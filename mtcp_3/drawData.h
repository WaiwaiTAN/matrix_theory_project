#ifndef DRAWDATA_H
#define DRAWDATA_H

#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>
#include <QtCharts/QChartView>
#include <QtCharts/QScatterSeries>
#include <QtCharts/QLineSeries>
#include <Eigen/Dense>
#include <iostream>
QT_CHARTS_USE_NAMESPACE

/*!
 *  \brief drawData Call this function to draw scatter chart and line chart
 *  \param argc The number of arguments if program is executed by something like "*.exe -rf", just ignore it.
 *  \param argv The arguments mentioned before, just ignore it.
 *  \param scatter_mat A n by 2 matrix in which x-y data in a scatter chart is stored.
 *  \param line_mat An m by 2 matrix in which x-y data in a line chart is stored.
 *  \param The result of the window execution.
 */
int drawData(int argc, char *argv[], Eigen::MatrixXd scatter_mat, Eigen::MatrixXd line_mat);

#endif // DRAWDATA_H

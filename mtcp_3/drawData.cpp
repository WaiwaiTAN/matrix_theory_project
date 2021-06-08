#include "drawData.h"

int drawData(int argc, char *argv[], Eigen::MatrixXd scatter_mat, Eigen::MatrixXd line_mat)
{
    QApplication a(argc, argv);

//![1]
    QLineSeries *line_series = new QLineSeries();
    auto scatter_series = new QScatterSeries();
    scatter_series->setMarkerShape(QScatterSeries::MarkerShapeCircle);
    scatter_series->setMarkerSize(15.0);
//![1]

//![2]
    int n = scatter_mat.rows();
    for (int i = 0; i<n; i++)
    {
        scatter_series->append(scatter_mat(i,0), scatter_mat(i,1));
    }
    n = line_mat.rows();
    for (int i = 0; i<n; i++)
    {
        line_series->append(line_mat(i,0), line_mat(i,1));
    }
//![2]

//![3]
    QChart *chart = new QChart();
    chart->legend()->hide();
    chart->addSeries(line_series);
    chart->addSeries(scatter_series);
    chart->createDefaultAxes();
    chart->setTitle("Fitting Result");
//![3]

//![4]
    QChartView *chartView = new QChartView(chart);
    chartView->setRenderHint(QPainter::Antialiasing);
//![4]


//![5]
    QMainWindow window;
    window.setCentralWidget(chartView);
    window.resize(400, 300);
    window.show();
//![5]

    return a.exec();
}

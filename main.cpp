#include "mainwindow.h"
#include <QApplication>

#include "chartshelper.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.showMaximized();

    return a.exec();
}

int normal(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.showMaximized();

    return a.exec();
}

//int withChart(int argc, char *argv[])
//{
//    QApplication a(argc, argv);

//    ChartsHelper chartsHelper;
//    QChartView* chartView = chartsHelper.biuldChart();

//    QMainWindow window;
//    window.setCentralWidget(chartView);
//    window.resize(400, 300);
//    window.show();

//    return a.exec();
//}

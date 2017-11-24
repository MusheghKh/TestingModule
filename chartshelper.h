#ifndef CHARTSHELPER_H
#define CHARTSHELPER_H

#include <QtCharts>

class ChartsHelper
{
public:
    ChartsHelper(const QString &title);
    QChartView* biuldChart();
    void appendPart(QString label, qreal percent);
    void appendSlicePart(QString label, qreal percent);
    void reset(const QString &title);

private:
    QString chartTitle;
    QPieSeries* series;
};

#endif // CHARTSHELPER_H

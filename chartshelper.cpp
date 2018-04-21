#include "chartshelper.h"

ChartsHelper::ChartsHelper(const QString &title)
{
    chartTitle = title;
    series = new QPieSeries();
    series->setHoleSize(0.35);
}

void ChartsHelper::appendPart(QString label, qreal percent)
{
    QPieSlice *slice = series->append(label, percent);
    slice->setColor(" #4F1B68");
    slice->setLabelVisible();
}

void ChartsHelper::appendSlicePart(QString label, qreal percent)
{
    QPieSlice *slice = series->append(label, percent);
    slice->setColor(QColor("#D90404"));
    slice->setExploded();
    slice->setLabelVisible();
}


QChartView* ChartsHelper::biuldChart()
{
//    QPieSeries *series = new QPieSeries();
//    series->setHoleSize(0.35);
//    series->append("Protein 4.2%", 4.2);
//    QPieSlice *slice = series->append("Fat 15.6%", 15.6);
//    slice->setExploded();
//    slice->setLabelVisible();
//    series->append("Other 23.8%", 23.8);
//    series->append("Carbs 56.4%", 56.4);

    QChartView *chartView = new QChartView();
    chartView->setRenderHint(QPainter::Antialiasing);
    chartView->chart()->setTitle(chartTitle);
    chartView->chart()->addSeries(series);
    chartView->chart()->legend()->setAlignment(Qt::AlignBottom);
    chartView->chart()->setTheme(QChart::ChartThemeBlueCerulean);
    chartView->chart()->legend()->setFont(QFont("Arial", 7));

    return chartView;
}

void ChartsHelper::reset(const QString &title)
{
    chartTitle = title;
    series = new QPieSeries();
    series->setHoleSize(0.35);
}

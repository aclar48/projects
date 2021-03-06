/**
  @file widgetlinechart.h
  @author Alex Clarke, Melanie Imough, Jen Stewart
  @version 1.0

  @section DESCRIPTION

  Header for a window displaying a line chart
  */

#ifndef WIDGETLINECHART_H
#define WIDGETLINECHART_H

#include <QWidget>
#include "measure.h"
#include "qcustomplot.h"
#include "graphtemplate.h"

namespace Ui {
class WidgetLineChart;
}

class WidgetLineChart : public QWidget
{
    Q_OBJECT
    
public:
    explicit WidgetLineChart(QWidget *parent = 0);
    WidgetLineChart(QWidget *parent, const Measure &meas, const std::pair<double,double> &range);
    ~WidgetLineChart();
    
    void drawChartDefault();

private slots:
    void on_listLineChartMunicipality_itemSelectionChanged();
    void on_radioButtonMeanAllDataBar_toggled(bool checked);
    void on_pushButtonSaveLineData_clicked();
    void on_pushButtonRefresh_clicked();
    void on_listLineChartYears_itemSelectionChanged();

    void titleDoubleClick(QMouseEvent* event, QCPPlotTitle* title);
    void axisLabelDoubleClick(QCPAxis *axis, QCPAxis::SelectablePart part);
    void legendDoubleClick(QCPLegend *legend, QCPAbstractLegendItem *item);
    void selectionChanged();
    void mousePress();
    void mouseWheel();
    void contextMenuRequest(QPoint pos);
    void selectImageBackground();
    void selectImageAxisBackground();
    void changeLegendColor();
    void changeColorLine();
    void changeAxisColor();
    void changeBackgroundColor();
    void moveLegend();

    void on_pushButtonLoadTemp_clicked();

    void on_pushButtonSaveTemp_clicked();

signals:
    void plottableClick(QCPAbstractPlottable*,QMouseEvent*);

private:
    void drawChart();
    void drawYear(const int &sel);
    void drawAverage();

    void setImageBackground(const QString &path);
    void setBGAxisImage(const QString &path);
    void setBGColour(const QColor &col);
    void setAxisBGColor(const QColor &col);
    void setLegendColor(const QColor &col);
    void setLegendPos(const int &pos);

    Ui::WidgetLineChart *ui;
    Measure *_meas; //active measure
    GraphTemplate *_currentTemp;
    //QString measName;
    QString _dirname;
    std::pair<double,double> _range;
    int _lowrange; //low range of the data
    int _highrange; //high range of the data
};

#endif // WIDGETLINECHART_H

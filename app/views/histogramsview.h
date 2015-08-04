#ifndef HISTOGRAMSVIEW_H
#define HISTOGRAMSVIEW_H

#include "models/histogramsdrawingdata.h"
#include "models/histogramseriesdata.h"

#include <QMainWindow>
#include <qwt.h>
#include <qwt_plot.h>
#include <qwt_plot_curve.h>
#include <qwt_symbol.h>
#include <qwt_legend.h>
#include <qwt_series_data.h>
#include <qwt_plot_grid.h>

namespace Ui {
class HistogramsView;
}

class HistogramsView : public QMainWindow
{
    Q_OBJECT

public:
    explicit HistogramsView(QWidget *parent = 0);
    ~HistogramsView();

    HistogramsDrawingData *getData() const;
    void setData(HistogramsDrawingData *value);

private slots:
    void on_cbxView_currentIndexChanged(int index);

private:
    Ui::HistogramsView *ui;
    QwtPlotGrid *grid;
    QwtPlot *plot;
    QwtPlotCurve* coords;
    QwtPlotCurve* dims;

    HistogramSeriesData* dataCoords;
    HistogramSeriesData* dataDims;
    HistogramsDrawingData* data;
    int currentIndex;
};

#endif // HISTOGRAMSVIEW_H

#include "histogramsview.h"
#include "ui_histogramsview.h"

HistogramsView::HistogramsView(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::HistogramsView),
    currentIndex(0)
{
    this->ui->setupUi(this);
    this->plot = new QwtPlot(this);
    plot->setTitle("Histogram");
    plot->setCanvasBackground(QColor(Qt::white));
    this->grid = new QwtPlotGrid();
    grid->enableXMin(true);
    grid->enableYMin(true);
    grid->setMajorPen(QPen(Qt::black, 0, Qt::DotLine));
    grid->setMinorPen(QPen(Qt::gray, 0 , Qt::DotLine));
    grid->attach(plot);
    this->dims = new QwtPlotCurve("Nonzero dimensions count");
    this->dims->setBrush(QBrush(Qt::yellow));
    this->coords = new QwtPlotCurve("Coord values");
    this->coords->setBrush(QBrush(Qt::green));
    this->layout()->addWidget(plot);
    this->dataCoords = new HistogramSeriesData();
    this->dataDims = new HistogramSeriesData();
}

HistogramsView::~HistogramsView()
{
    delete this->ui;
//    delete this->data;
    delete this->grid;
    delete this->coords;
    delete this->dims;
    delete this->dataCoords;
    delete this->dataDims;
}

void HistogramsView::on_cbxView_currentIndexChanged(int index)
{
    this->currentIndex = index;
    QPointF max, min;
    switch(index)
    {
    case 0:
        this->coords->attach(this->plot);
        max = this->data->getMaxCoords();
        min = this->data->getMinCoords();
        break;
    case 1:
        this->dims->attach(this->plot);
        max = this->data->getMaxDims();
        min = this->data->getMinDims();
        break;
    default:
        break;
    }

    this->plot->setAxisScale(QwtPlot::yLeft, 0.0, max.ry(), min.ry() / 2.0);
    this->plot->setAxisScale(QwtPlot::xBottom, 0.0, max.rx(), min.rx() / 2.0);
    this->plot->setAutoReplot(true);
    this->plot->replot();
    this->plot->repaint();
}

HistogramsDrawingData *HistogramsView::getData() const
{
    return data;
}

void HistogramsView::setData(HistogramsDrawingData *value)
{
    data = value;
    this->dataCoords->setSamples(value->getCoords());
    this->dataDims->setSamples(value->getDims());
    this->coords->setData(this->dataCoords);
    this->dims->setData(this->dataDims);
    this->on_cbxView_currentIndexChanged(this->currentIndex);
}


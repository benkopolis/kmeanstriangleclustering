#include "clusteringview.h"
#include "ui_clusteringview.h"

ClusteringView::ClusteringView(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::ClusteringView)
{
    ui->setupUi(this);
}

ClusteringView::~ClusteringView()
{
    delete ui;
}

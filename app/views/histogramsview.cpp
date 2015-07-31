#include "histogramsview.h"
#include "ui_histogramsview.h"

HistogramsView::HistogramsView(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::HistogramsView)
{
    ui->setupUi(this);
}

HistogramsView::~HistogramsView()
{
    delete ui;
}

void HistogramsView::on_cbxView_currentIndexChanged(int index)
{
    switch(index)
    {
    case 0:
        break;
    case 1:
        break;
    default:
        break;
    }
}

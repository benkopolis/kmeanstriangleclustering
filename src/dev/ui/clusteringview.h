#ifndef CLUSTERINGVIEW_H
#define CLUSTERINGVIEW_H

#include <QWi>

namespace Ui {
    class ClusteringView;
}

class ClusteringView : public QMainWindow
{
    Q_OBJECT

public:
    explicit ClusteringView(QWidget *parent = 0);
    ~ClusteringView();

private:
    Ui::ClusteringView *ui;
};

#endif // CLUSTERINGVIEW_H

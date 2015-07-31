#ifndef HISTOGRAMSVIEW_H
#define HISTOGRAMSVIEW_H

#include <QMainWindow>

namespace Ui {
class HistogramsView;
}

class HistogramsView : public QMainWindow
{
    Q_OBJECT

public:
    explicit HistogramsView(QWidget *parent = 0);
    ~HistogramsView();

private slots:
    void on_cbxView_currentIndexChanged(int index);

private:
    Ui::HistogramsView *ui;
};

#endif // HISTOGRAMSVIEW_H

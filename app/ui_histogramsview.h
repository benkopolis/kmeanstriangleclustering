/********************************************************************************
** Form generated from reading UI file 'histogramsview.ui'
**
** Created by: Qt User Interface Compiler version 5.4.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_HISTOGRAMSVIEW_H
#define UI_HISTOGRAMSVIEW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_HistogramsView
{
public:
    QWidget *centralwidget;
    QWidget *widget;
    QVBoxLayout *verticalLayout;
    QComboBox *cbxView;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *HistogramsView)
    {
        if (HistogramsView->objectName().isEmpty())
            HistogramsView->setObjectName(QStringLiteral("HistogramsView"));
        HistogramsView->resize(800, 600);
        centralwidget = new QWidget(HistogramsView);
        centralwidget->setObjectName(QStringLiteral("centralwidget"));
        widget = new QWidget(centralwidget);
        widget->setObjectName(QStringLiteral("widget"));
        widget->setGeometry(QRect(7, 11, 791, 431));
        verticalLayout = new QVBoxLayout(widget);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        cbxView = new QComboBox(widget);
        cbxView->setObjectName(QStringLiteral("cbxView"));

        verticalLayout->addWidget(cbxView);

        HistogramsView->setCentralWidget(centralwidget);
        statusbar = new QStatusBar(HistogramsView);
        statusbar->setObjectName(QStringLiteral("statusbar"));
        HistogramsView->setStatusBar(statusbar);

        retranslateUi(HistogramsView);

        QMetaObject::connectSlotsByName(HistogramsView);
    } // setupUi

    void retranslateUi(QMainWindow *HistogramsView)
    {
        HistogramsView->setWindowTitle(QApplication::translate("HistogramsView", "MainWindow", 0));
        cbxView->clear();
        cbxView->insertItems(0, QStringList()
         << QApplication::translate("HistogramsView", "Coords values frequency", "0")
         << QApplication::translate("HistogramsView", "Nonzero dimensions count frequency", "1")
        );
    } // retranslateUi

};

namespace Ui {
    class HistogramsView: public Ui_HistogramsView {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_HISTOGRAMSVIEW_H

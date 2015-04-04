/********************************************************************************
** Form generated from reading UI file 'clusteringview.ui'
**
** Created by: Qt User Interface Compiler version 4.8.6
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CLUSTERINGVIEW_H
#define UI_CLUSTERINGVIEW_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QHeaderView>
#include <QtGui/QMainWindow>
#include <QtGui/QMenuBar>
#include <QtGui/QStatusBar>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_ClusteringView
{
public:
    QMenuBar *menubar;
    QWidget *centralwidget;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *ClusteringView)
    {
        if (ClusteringView->objectName().isEmpty())
            ClusteringView->setObjectName(QString::fromUtf8("ClusteringView"));
        ClusteringView->resize(480, 640);
        menubar = new QMenuBar(ClusteringView);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        ClusteringView->setMenuBar(menubar);
        centralwidget = new QWidget(ClusteringView);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        ClusteringView->setCentralWidget(centralwidget);
        statusbar = new QStatusBar(ClusteringView);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        ClusteringView->setStatusBar(statusbar);

        retranslateUi(ClusteringView);

        QMetaObject::connectSlotsByName(ClusteringView);
    } // setupUi

    void retranslateUi(QMainWindow *ClusteringView)
    {
        ClusteringView->setWindowTitle(QApplication::translate("ClusteringView", "MainWindow", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class ClusteringView: public Ui_ClusteringView {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CLUSTERINGVIEW_H

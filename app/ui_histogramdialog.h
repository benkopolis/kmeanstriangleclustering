/********************************************************************************
** Form generated from reading UI file 'histogramdialog.ui'
**
** Created by: Qt User Interface Compiler version 5.4.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_HISTOGRAMDIALOG_H
#define UI_HISTOGRAMDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_HistogramDialog
{
public:
    QWidget *widget;
    QVBoxLayout *verticalLayout;
    QCheckBox *cbxRead;
    QCheckBox *cbxCount;
    QCheckBox *cbxWrite;
    QPushButton *btnCoordsHist;
    QPushButton *btnDimsHist;
    QPushButton *btnClose;

    void setupUi(QDialog *HistogramDialog)
    {
        if (HistogramDialog->objectName().isEmpty())
            HistogramDialog->setObjectName(QStringLiteral("HistogramDialog"));
        HistogramDialog->resize(400, 300);
        widget = new QWidget(HistogramDialog);
        widget->setObjectName(QStringLiteral("widget"));
        widget->setGeometry(QRect(10, 10, 371, 261));
        verticalLayout = new QVBoxLayout(widget);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        cbxRead = new QCheckBox(widget);
        cbxRead->setObjectName(QStringLiteral("cbxRead"));
        cbxRead->setEnabled(false);

        verticalLayout->addWidget(cbxRead);

        cbxCount = new QCheckBox(widget);
        cbxCount->setObjectName(QStringLiteral("cbxCount"));
        cbxCount->setEnabled(false);

        verticalLayout->addWidget(cbxCount);

        cbxWrite = new QCheckBox(widget);
        cbxWrite->setObjectName(QStringLiteral("cbxWrite"));
        cbxWrite->setEnabled(false);

        verticalLayout->addWidget(cbxWrite);

        btnCoordsHist = new QPushButton(widget);
        btnCoordsHist->setObjectName(QStringLiteral("btnCoordsHist"));

        verticalLayout->addWidget(btnCoordsHist);

        btnDimsHist = new QPushButton(widget);
        btnDimsHist->setObjectName(QStringLiteral("btnDimsHist"));

        verticalLayout->addWidget(btnDimsHist);

        btnClose = new QPushButton(widget);
        btnClose->setObjectName(QStringLiteral("btnClose"));
        btnClose->setEnabled(false);

        verticalLayout->addWidget(btnClose);


        retranslateUi(HistogramDialog);

        QMetaObject::connectSlotsByName(HistogramDialog);
    } // setupUi

    void retranslateUi(QDialog *HistogramDialog)
    {
        HistogramDialog->setWindowTitle(QApplication::translate("HistogramDialog", "Dialog", 0));
        cbxRead->setText(QApplication::translate("HistogramDialog", "Read tf-idf file", 0));
        cbxCount->setText(QApplication::translate("HistogramDialog", "Count frequencies", 0));
        cbxWrite->setText(QApplication::translate("HistogramDialog", "Store results", 0));
        btnCoordsHist->setText(QApplication::translate("HistogramDialog", "View coordinates values frequency", 0));
        btnDimsHist->setText(QApplication::translate("HistogramDialog", "View nonzero dimensions count frequency", 0));
        btnClose->setText(QApplication::translate("HistogramDialog", "Close", 0));
    } // retranslateUi

};

namespace Ui {
    class HistogramDialog: public Ui_HistogramDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_HISTOGRAMDIALOG_H

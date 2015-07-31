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
    QWidget *layoutWidget;
    QVBoxLayout *verticalLayout;
    QCheckBox *cbxRead;
    QCheckBox *cbxWrite;
    QPushButton *btnView;
    QPushButton *btnClose;

    void setupUi(QDialog *HistogramDialog)
    {
        if (HistogramDialog->objectName().isEmpty())
            HistogramDialog->setObjectName(QStringLiteral("HistogramDialog"));
        HistogramDialog->resize(400, 300);
        layoutWidget = new QWidget(HistogramDialog);
        layoutWidget->setObjectName(QStringLiteral("layoutWidget"));
        layoutWidget->setGeometry(QRect(10, 10, 371, 261));
        verticalLayout = new QVBoxLayout(layoutWidget);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        cbxRead = new QCheckBox(layoutWidget);
        cbxRead->setObjectName(QStringLiteral("cbxRead"));
        cbxRead->setEnabled(false);

        verticalLayout->addWidget(cbxRead);

        cbxWrite = new QCheckBox(layoutWidget);
        cbxWrite->setObjectName(QStringLiteral("cbxWrite"));
        cbxWrite->setEnabled(false);

        verticalLayout->addWidget(cbxWrite);

        btnView = new QPushButton(layoutWidget);
        btnView->setObjectName(QStringLiteral("btnView"));
        btnView->setEnabled(false);

        verticalLayout->addWidget(btnView);

        btnClose = new QPushButton(layoutWidget);
        btnClose->setObjectName(QStringLiteral("btnClose"));
        btnClose->setEnabled(false);

        verticalLayout->addWidget(btnClose);


        retranslateUi(HistogramDialog);

        QMetaObject::connectSlotsByName(HistogramDialog);
    } // setupUi

    void retranslateUi(QDialog *HistogramDialog)
    {
        HistogramDialog->setWindowTitle(QApplication::translate("HistogramDialog", "Dialog", 0));
        cbxRead->setText(QApplication::translate("HistogramDialog", "Read and process tf-idf file", 0));
        cbxWrite->setText(QApplication::translate("HistogramDialog", "Store results", 0));
        btnView->setText(QApplication::translate("HistogramDialog", "View histograms", 0));
        btnClose->setText(QApplication::translate("HistogramDialog", "Close", 0));
    } // retranslateUi

};

namespace Ui {
    class HistogramDialog: public Ui_HistogramDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_HISTOGRAMDIALOG_H

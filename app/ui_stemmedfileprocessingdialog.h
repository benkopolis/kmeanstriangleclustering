/********************************************************************************
** Form generated from reading UI file 'stemmedfileprocessingdialog.ui'
**
** Created by: Qt User Interface Compiler version 5.4.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_STEMMEDFILEPROCESSINGDIALOG_H
#define UI_STEMMEDFILEPROCESSINGDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_StemmedFileProcessingDialog
{
public:
    QVBoxLayout *verticalLayout_2;
    QVBoxLayout *verticalLayout;
    QCheckBox *cbxReading;
    QCheckBox *cbxTfidf;
    QCheckBox *cbxWriting;
    QCheckBox *cbxDone;
    QPushButton *btnClose;

    void setupUi(QDialog *StemmedFileProcessingDialog)
    {
        if (StemmedFileProcessingDialog->objectName().isEmpty())
            StemmedFileProcessingDialog->setObjectName(QStringLiteral("StemmedFileProcessingDialog"));
        StemmedFileProcessingDialog->resize(400, 239);
        verticalLayout_2 = new QVBoxLayout(StemmedFileProcessingDialog);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        cbxReading = new QCheckBox(StemmedFileProcessingDialog);
        cbxReading->setObjectName(QStringLiteral("cbxReading"));
        cbxReading->setEnabled(false);

        verticalLayout->addWidget(cbxReading);

        cbxTfidf = new QCheckBox(StemmedFileProcessingDialog);
        cbxTfidf->setObjectName(QStringLiteral("cbxTfidf"));
        cbxTfidf->setEnabled(false);

        verticalLayout->addWidget(cbxTfidf);

        cbxWriting = new QCheckBox(StemmedFileProcessingDialog);
        cbxWriting->setObjectName(QStringLiteral("cbxWriting"));
        cbxWriting->setEnabled(false);

        verticalLayout->addWidget(cbxWriting);

        cbxDone = new QCheckBox(StemmedFileProcessingDialog);
        cbxDone->setObjectName(QStringLiteral("cbxDone"));
        cbxDone->setEnabled(false);

        verticalLayout->addWidget(cbxDone);

        btnClose = new QPushButton(StemmedFileProcessingDialog);
        btnClose->setObjectName(QStringLiteral("btnClose"));
        btnClose->setEnabled(false);

        verticalLayout->addWidget(btnClose);


        verticalLayout_2->addLayout(verticalLayout);


        retranslateUi(StemmedFileProcessingDialog);

        QMetaObject::connectSlotsByName(StemmedFileProcessingDialog);
    } // setupUi

    void retranslateUi(QDialog *StemmedFileProcessingDialog)
    {
        StemmedFileProcessingDialog->setWindowTitle(QApplication::translate("StemmedFileProcessingDialog", "Dialog", 0));
        cbxReading->setText(QApplication::translate("StemmedFileProcessingDialog", "Reading stemmed documents from", 0));
        cbxTfidf->setText(QApplication::translate("StemmedFileProcessingDialog", "Counting tfidf indexes for words", 0));
        cbxWriting->setText(QApplication::translate("StemmedFileProcessingDialog", "Writing to file:", 0));
        cbxDone->setText(QApplication::translate("StemmedFileProcessingDialog", "All done, you can close this window", 0));
        btnClose->setText(QApplication::translate("StemmedFileProcessingDialog", "Close", 0));
    } // retranslateUi

};

namespace Ui {
    class StemmedFileProcessingDialog: public Ui_StemmedFileProcessingDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_STEMMEDFILEPROCESSINGDIALOG_H

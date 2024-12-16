/********************************************************************************
** Form generated from reading UI file 'busydialog.ui'
**
** Created by: Qt User Interface Compiler version 6.8.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_BUSYDIALOG_H
#define UI_BUSYDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QLabel>
#include <QtWidgets/QProgressBar>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_BusyDialog
{
public:
    QVBoxLayout *verticalLayout;
    QSpacerItem *verticalSpacer_2;
    QProgressBar *progressBar;
    QLabel *busyStaicText;
    QLabel *busyDynamicText;
    QSpacerItem *verticalSpacer;

    void setupUi(QDialog *BusyDialog)
    {
        if (BusyDialog->objectName().isEmpty())
            BusyDialog->setObjectName("BusyDialog");
        BusyDialog->setWindowModality(Qt::ApplicationModal);
        BusyDialog->resize(309, 116);
        verticalLayout = new QVBoxLayout(BusyDialog);
        verticalLayout->setObjectName("verticalLayout");
        verticalSpacer_2 = new QSpacerItem(20, 40, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        verticalLayout->addItem(verticalSpacer_2);

        progressBar = new QProgressBar(BusyDialog);
        progressBar->setObjectName("progressBar");
        progressBar->setMaximum(0);
        progressBar->setValue(-1);
        progressBar->setTextVisible(false);

        verticalLayout->addWidget(progressBar);

        busyStaicText = new QLabel(BusyDialog);
        busyStaicText->setObjectName("busyStaicText");
        busyStaicText->setAlignment(Qt::AlignCenter);

        verticalLayout->addWidget(busyStaicText);

        busyDynamicText = new QLabel(BusyDialog);
        busyDynamicText->setObjectName("busyDynamicText");
        busyDynamicText->setAlignment(Qt::AlignCenter);

        verticalLayout->addWidget(busyDynamicText);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        verticalLayout->addItem(verticalSpacer);


        retranslateUi(BusyDialog);

        QMetaObject::connectSlotsByName(BusyDialog);
    } // setupUi

    void retranslateUi(QDialog *BusyDialog)
    {
        BusyDialog->setWindowTitle(QCoreApplication::translate("BusyDialog", "System Busy", nullptr));
        busyStaicText->setText(QCoreApplication::translate("BusyDialog", "System Busy...Please Wait...", nullptr));
        busyDynamicText->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class BusyDialog: public Ui_BusyDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_BUSYDIALOG_H

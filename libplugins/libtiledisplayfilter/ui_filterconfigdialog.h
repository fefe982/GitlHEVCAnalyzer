/********************************************************************************
** Form generated from reading UI file 'filterconfigdialog.ui'
**
** Created by: Qt User Interface Compiler version 6.8.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_FILTERCONFIGDIALOG_H
#define UI_FILTERCONFIGDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QAbstractButton>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_FilterConfigDialog
{
public:
    QVBoxLayout *verticalLayout;
    QVBoxLayout *contentLayout;
    QSpacerItem *verticalSpacer;
    QDialogButtonBox *buttonBox;

    void setupUi(QDialog *FilterConfigDialog)
    {
        if (FilterConfigDialog->objectName().isEmpty())
            FilterConfigDialog->setObjectName("FilterConfigDialog");
        FilterConfigDialog->resize(226, 73);
        verticalLayout = new QVBoxLayout(FilterConfigDialog);
        verticalLayout->setSpacing(15);
        verticalLayout->setObjectName("verticalLayout");
        contentLayout = new QVBoxLayout();
        contentLayout->setObjectName("contentLayout");

        verticalLayout->addLayout(contentLayout);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        verticalLayout->addItem(verticalSpacer);

        buttonBox = new QDialogButtonBox(FilterConfigDialog);
        buttonBox->setObjectName("buttonBox");
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);

        verticalLayout->addWidget(buttonBox);


        retranslateUi(FilterConfigDialog);
        QObject::connect(buttonBox, &QDialogButtonBox::accepted, FilterConfigDialog, qOverload<>(&QDialog::accept));
        QObject::connect(buttonBox, &QDialogButtonBox::rejected, FilterConfigDialog, qOverload<>(&QDialog::reject));

        QMetaObject::connectSlotsByName(FilterConfigDialog);
    } // setupUi

    void retranslateUi(QDialog *FilterConfigDialog)
    {
        FilterConfigDialog->setWindowTitle(QCoreApplication::translate("FilterConfigDialog", "Dialog", nullptr));
    } // retranslateUi

};

namespace Ui {
    class FilterConfigDialog: public Ui_FilterConfigDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_FILTERCONFIGDIALOG_H

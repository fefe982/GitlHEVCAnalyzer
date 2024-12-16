/********************************************************************************
** Form generated from reading UI file 'filterconfigradios.ui'
**
** Created by: Qt User Interface Compiler version 6.8.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_FILTERCONFIGRADIOS_H
#define UI_FILTERCONFIGRADIOS_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_FilterConfigRadios
{
public:
    QVBoxLayout *verticalLayout;
    QVBoxLayout *content;

    void setupUi(QWidget *FilterConfigRadios)
    {
        if (FilterConfigRadios->objectName().isEmpty())
            FilterConfigRadios->setObjectName("FilterConfigRadios");
        FilterConfigRadios->resize(62, 16);
        verticalLayout = new QVBoxLayout(FilterConfigRadios);
        verticalLayout->setObjectName("verticalLayout");
        verticalLayout->setContentsMargins(-1, 0, -1, 0);
        content = new QVBoxLayout();
        content->setSpacing(10);
        content->setObjectName("content");

        verticalLayout->addLayout(content);


        retranslateUi(FilterConfigRadios);

        QMetaObject::connectSlotsByName(FilterConfigRadios);
    } // setupUi

    void retranslateUi(QWidget *FilterConfigRadios)
    {
        FilterConfigRadios->setWindowTitle(QCoreApplication::translate("FilterConfigRadios", "Form", nullptr));
    } // retranslateUi

};

namespace Ui {
    class FilterConfigRadios: public Ui_FilterConfigRadios {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_FILTERCONFIGRADIOS_H

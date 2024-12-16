/********************************************************************************
** Form generated from reading UI file 'filterconfigcombobox.ui'
**
** Created by: Qt User Interface Compiler version 6.8.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_FILTERCONFIGCOMBOBOX_H
#define UI_FILTERCONFIGCOMBOBOX_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_FilterConfigComboBox
{
public:
    QHBoxLayout *horizontalLayout;
    QComboBox *comboBox;
    QLabel *label;
    QSpacerItem *horizontalSpacer;

    void setupUi(QWidget *FilterConfigComboBox)
    {
        if (FilterConfigComboBox->objectName().isEmpty())
            FilterConfigComboBox->setObjectName("FilterConfigComboBox");
        FilterConfigComboBox->resize(281, 20);
        horizontalLayout = new QHBoxLayout(FilterConfigComboBox);
        horizontalLayout->setObjectName("horizontalLayout");
        horizontalLayout->setContentsMargins(-1, 0, -1, 0);
        comboBox = new QComboBox(FilterConfigComboBox);
        comboBox->setObjectName("comboBox");

        horizontalLayout->addWidget(comboBox);

        label = new QLabel(FilterConfigComboBox);
        label->setObjectName("label");

        horizontalLayout->addWidget(label);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);


        retranslateUi(FilterConfigComboBox);

        QMetaObject::connectSlotsByName(FilterConfigComboBox);
    } // setupUi

    void retranslateUi(QWidget *FilterConfigComboBox)
    {
        FilterConfigComboBox->setWindowTitle(QCoreApplication::translate("FilterConfigComboBox", "Form", nullptr));
        label->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class FilterConfigComboBox: public Ui_FilterConfigComboBox {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_FILTERCONFIGCOMBOBOX_H

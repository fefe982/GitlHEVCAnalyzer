/********************************************************************************
** Form generated from reading UI file 'filterconfigcheckbox.ui'
**
** Created by: Qt User Interface Compiler version 6.8.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_FILTERCONFIGCHECKBOX_H
#define UI_FILTERCONFIGCHECKBOX_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_FilterConfigCheckBox
{
public:
    QHBoxLayout *horizontalLayout;
    QCheckBox *checkBox;
    QLabel *discriptionLabel;
    QSpacerItem *horizontalSpacer;

    void setupUi(QWidget *FilterConfigCheckBox)
    {
        if (FilterConfigCheckBox->objectName().isEmpty())
            FilterConfigCheckBox->setObjectName("FilterConfigCheckBox");
        FilterConfigCheckBox->resize(289, 22);
        horizontalLayout = new QHBoxLayout(FilterConfigCheckBox);
        horizontalLayout->setSpacing(0);
        horizontalLayout->setObjectName("horizontalLayout");
        horizontalLayout->setContentsMargins(-1, 0, -1, 0);
        checkBox = new QCheckBox(FilterConfigCheckBox);
        checkBox->setObjectName("checkBox");

        horizontalLayout->addWidget(checkBox);

        discriptionLabel = new QLabel(FilterConfigCheckBox);
        discriptionLabel->setObjectName("discriptionLabel");

        horizontalLayout->addWidget(discriptionLabel);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);


        retranslateUi(FilterConfigCheckBox);

        QMetaObject::connectSlotsByName(FilterConfigCheckBox);
    } // setupUi

    void retranslateUi(QWidget *FilterConfigCheckBox)
    {
        FilterConfigCheckBox->setWindowTitle(QCoreApplication::translate("FilterConfigCheckBox", "Form", nullptr));
        checkBox->setText(QCoreApplication::translate("FilterConfigCheckBox", "LABEL", nullptr));
        discriptionLabel->setText(QCoreApplication::translate("FilterConfigCheckBox", "DISCRIPTION", nullptr));
    } // retranslateUi

};

namespace Ui {
    class FilterConfigCheckBox: public Ui_FilterConfigCheckBox {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_FILTERCONFIGCHECKBOX_H

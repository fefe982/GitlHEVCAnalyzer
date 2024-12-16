/********************************************************************************
** Form generated from reading UI file 'filterconfigslider.ui'
**
** Created by: Qt User Interface Compiler version 6.8.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_FILTERCONFIGSLIDER_H
#define UI_FILTERCONFIGSLIDER_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QSlider>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_FilterConfigSlider
{
public:
    QHBoxLayout *horizontalLayout;
    QSlider *slider;
    QHBoxLayout *horizontalLayout_2;
    QLabel *sliderLabel;
    QLabel *sliderValue;

    void setupUi(QWidget *FilterConfigSlider)
    {
        if (FilterConfigSlider->objectName().isEmpty())
            FilterConfigSlider->setObjectName("FilterConfigSlider");
        FilterConfigSlider->resize(166, 22);
        horizontalLayout = new QHBoxLayout(FilterConfigSlider);
        horizontalLayout->setObjectName("horizontalLayout");
        horizontalLayout->setContentsMargins(-1, 0, -1, 0);
        slider = new QSlider(FilterConfigSlider);
        slider->setObjectName("slider");
        slider->setMaximum(100);
        slider->setOrientation(Qt::Horizontal);

        horizontalLayout->addWidget(slider);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName("horizontalLayout_2");
        sliderLabel = new QLabel(FilterConfigSlider);
        sliderLabel->setObjectName("sliderLabel");

        horizontalLayout_2->addWidget(sliderLabel);

        sliderValue = new QLabel(FilterConfigSlider);
        sliderValue->setObjectName("sliderValue");

        horizontalLayout_2->addWidget(sliderValue);


        horizontalLayout->addLayout(horizontalLayout_2);


        retranslateUi(FilterConfigSlider);

        QMetaObject::connectSlotsByName(FilterConfigSlider);
    } // setupUi

    void retranslateUi(QWidget *FilterConfigSlider)
    {
        FilterConfigSlider->setWindowTitle(QCoreApplication::translate("FilterConfigSlider", "Form", nullptr));
        sliderLabel->setText(QCoreApplication::translate("FilterConfigSlider", "LABEL", nullptr));
        sliderValue->setText(QCoreApplication::translate("FilterConfigSlider", "VALUE", nullptr));
    } // retranslateUi

};

namespace Ui {
    class FilterConfigSlider: public Ui_FilterConfigSlider {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_FILTERCONFIGSLIDER_H

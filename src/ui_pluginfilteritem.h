/********************************************************************************
** Form generated from reading UI file 'pluginfilteritem.ui'
**
** Created by: Qt User Interface Compiler version 6.8.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PLUGINFILTERITEM_H
#define UI_PLUGINFILTERITEM_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QToolButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_PluginFilterItem
{
public:
    QHBoxLayout *horizontalLayout;
    QCheckBox *enableCheckBox;
    QLabel *filterNameLabel;
    QSpacerItem *horizontalSpacer;
    QToolButton *configBtn;

    void setupUi(QWidget *PluginFilterItem)
    {
        if (PluginFilterItem->objectName().isEmpty())
            PluginFilterItem->setObjectName("PluginFilterItem");
        PluginFilterItem->resize(168, 30);
        horizontalLayout = new QHBoxLayout(PluginFilterItem);
        horizontalLayout->setObjectName("horizontalLayout");
        horizontalLayout->setContentsMargins(3, 3, 3, 3);
        enableCheckBox = new QCheckBox(PluginFilterItem);
        enableCheckBox->setObjectName("enableCheckBox");

        horizontalLayout->addWidget(enableCheckBox);

        filterNameLabel = new QLabel(PluginFilterItem);
        filterNameLabel->setObjectName("filterNameLabel");

        horizontalLayout->addWidget(filterNameLabel);

        horizontalSpacer = new QSpacerItem(0, 5, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        configBtn = new QToolButton(PluginFilterItem);
        configBtn->setObjectName("configBtn");
        configBtn->setMinimumSize(QSize(0, 20));

        horizontalLayout->addWidget(configBtn);


        retranslateUi(PluginFilterItem);

        QMetaObject::connectSlotsByName(PluginFilterItem);
    } // setupUi

    void retranslateUi(QWidget *PluginFilterItem)
    {
        PluginFilterItem->setWindowTitle(QCoreApplication::translate("PluginFilterItem", "Form", nullptr));
        enableCheckBox->setText(QString());
        filterNameLabel->setText(QCoreApplication::translate("PluginFilterItem", "FilterName", nullptr));
        configBtn->setText(QCoreApplication::translate("PluginFilterItem", "CONFIG", nullptr));
    } // retranslateUi

};

namespace Ui {
    class PluginFilterItem: public Ui_PluginFilterItem {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PLUGINFILTERITEM_H

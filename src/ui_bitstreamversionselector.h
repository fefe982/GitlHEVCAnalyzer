/********************************************************************************
** Form generated from reading UI file 'bitstreamversionselector.ui'
**
** Created by: Qt User Interface Compiler version 6.8.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_BITSTREAMVERSIONSELECTOR_H
#define UI_BITSTREAMVERSIONSELECTOR_H

#include <QtCore/QVariant>
#include <QtWidgets/QAbstractButton>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_BitstreamVersionSelector
{
public:
    QVBoxLayout *verticalLayout;
    QGroupBox *groupBox;
    QHBoxLayout *horizontalLayout_2;
    QHBoxLayout *horizontalLayout;
    QVBoxLayout *verticalLayout_2;
    QRadioButton *version40;
    QRadioButton *version52;
    QRadioButton *version100;
    QRadioButton *version120;
    QRadioButton *version160;
    QDialogButtonBox *buttonBox;

    void setupUi(QDialog *BitstreamVersionSelector)
    {
        if (BitstreamVersionSelector->objectName().isEmpty())
            BitstreamVersionSelector->setObjectName("BitstreamVersionSelector");
        BitstreamVersionSelector->resize(197, 218);
        verticalLayout = new QVBoxLayout(BitstreamVersionSelector);
        verticalLayout->setObjectName("verticalLayout");
        groupBox = new QGroupBox(BitstreamVersionSelector);
        groupBox->setObjectName("groupBox");
        horizontalLayout_2 = new QHBoxLayout(groupBox);
        horizontalLayout_2->setObjectName("horizontalLayout_2");
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName("horizontalLayout");
        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setObjectName("verticalLayout_2");
        version40 = new QRadioButton(groupBox);
        version40->setObjectName("version40");
        version40->setChecked(true);

        verticalLayout_2->addWidget(version40);

        version52 = new QRadioButton(groupBox);
        version52->setObjectName("version52");
        version52->setEnabled(true);

        verticalLayout_2->addWidget(version52);

        version100 = new QRadioButton(groupBox);
        version100->setObjectName("version100");
        version100->setEnabled(true);

        verticalLayout_2->addWidget(version100);

        version120 = new QRadioButton(groupBox);
        version120->setObjectName("version120");

        verticalLayout_2->addWidget(version120);

        version160 = new QRadioButton(groupBox);
        version160->setObjectName("version160");

        verticalLayout_2->addWidget(version160);


        horizontalLayout->addLayout(verticalLayout_2);


        horizontalLayout_2->addLayout(horizontalLayout);


        verticalLayout->addWidget(groupBox);

        buttonBox = new QDialogButtonBox(BitstreamVersionSelector);
        buttonBox->setObjectName("buttonBox");
        buttonBox->setOrientation(Qt::Orientation::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::StandardButton::Ok);

        verticalLayout->addWidget(buttonBox);


        retranslateUi(BitstreamVersionSelector);
        QObject::connect(buttonBox, &QDialogButtonBox::accepted, BitstreamVersionSelector, qOverload<>(&QDialog::accept));
        QObject::connect(buttonBox, &QDialogButtonBox::rejected, BitstreamVersionSelector, qOverload<>(&QDialog::reject));

        QMetaObject::connectSlotsByName(BitstreamVersionSelector);
    } // setupUi

    void retranslateUi(QDialog *BitstreamVersionSelector)
    {
        BitstreamVersionSelector->setWindowTitle(QCoreApplication::translate("BitstreamVersionSelector", "Select HM Version", nullptr));
        groupBox->setTitle(QCoreApplication::translate("BitstreamVersionSelector", "HM Version", nullptr));
        version40->setText(QCoreApplication::translate("BitstreamVersionSelector", "HM 4.0", nullptr));
        version52->setText(QCoreApplication::translate("BitstreamVersionSelector", "HM 5.2", nullptr));
        version100->setText(QCoreApplication::translate("BitstreamVersionSelector", "HM 10.0", nullptr));
        version120->setText(QCoreApplication::translate("BitstreamVersionSelector", "HM 12.0", nullptr));
        version160->setText(QCoreApplication::translate("BitstreamVersionSelector", "HM 16.0", nullptr));
    } // retranslateUi

};

namespace Ui {
    class BitstreamVersionSelector: public Ui_BitstreamVersionSelector {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_BITSTREAMVERSIONSELECTOR_H

/********************************************************************************
** Form generated from reading UI file 'sequencelistitem.ui'
**
** Created by: Qt User Interface Compiler version 6.8.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SEQUENCELISTITEM_H
#define UI_SEQUENCELISTITEM_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_SequenceListItem
{
public:
    QHBoxLayout *horizontalLayout;
    QRadioButton *radioButton;
    QLabel *sequenceNameLabel;
    QSpacerItem *horizontalSpacer;
    QComboBox *yuvSelectionBox;
    QVBoxLayout *verticalLayout;
    QPushButton *closeBtn;

    void setupUi(QWidget *SequenceListItem)
    {
        if (SequenceListItem->objectName().isEmpty())
            SequenceListItem->setObjectName("SequenceListItem");
        SequenceListItem->resize(244, 36);
        horizontalLayout = new QHBoxLayout(SequenceListItem);
        horizontalLayout->setObjectName("horizontalLayout");
        horizontalLayout->setContentsMargins(3, 8, 3, 8);
        radioButton = new QRadioButton(SequenceListItem);
        radioButton->setObjectName("radioButton");

        horizontalLayout->addWidget(radioButton);

        sequenceNameLabel = new QLabel(SequenceListItem);
        sequenceNameLabel->setObjectName("sequenceNameLabel");

        horizontalLayout->addWidget(sequenceNameLabel);

        horizontalSpacer = new QSpacerItem(0, 15, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        yuvSelectionBox = new QComboBox(SequenceListItem);
        yuvSelectionBox->setObjectName("yuvSelectionBox");

        horizontalLayout->addWidget(yuvSelectionBox);

        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName("verticalLayout");
        closeBtn = new QPushButton(SequenceListItem);
        closeBtn->setObjectName("closeBtn");
        QSizePolicy sizePolicy(QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Minimum);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(closeBtn->sizePolicy().hasHeightForWidth());
        closeBtn->setSizePolicy(sizePolicy);
        closeBtn->setMinimumSize(QSize(21, 21));
        closeBtn->setMaximumSize(QSize(21, 21));

        verticalLayout->addWidget(closeBtn);


        horizontalLayout->addLayout(verticalLayout);


        retranslateUi(SequenceListItem);

        QMetaObject::connectSlotsByName(SequenceListItem);
    } // setupUi

    void retranslateUi(QWidget *SequenceListItem)
    {
        SequenceListItem->setWindowTitle(QCoreApplication::translate("SequenceListItem", "Form", nullptr));
        radioButton->setText(QString());
        sequenceNameLabel->setText(QCoreApplication::translate("SequenceListItem", "No Name", nullptr));
        closeBtn->setText(QCoreApplication::translate("SequenceListItem", "X", nullptr));
    } // retranslateUi

};

namespace Ui {
    class SequenceListItem: public Ui_SequenceListItem {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SEQUENCELISTITEM_H

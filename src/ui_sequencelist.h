/********************************************************************************
** Form generated from reading UI file 'sequencelist.ui'
**
** Created by: Qt User Interface Compiler version 6.8.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SEQUENCELIST_H
#define UI_SEQUENCELIST_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_SequenceList
{
public:
    QVBoxLayout *verticalLayout;

    void setupUi(QWidget *SequenceList)
    {
        if (SequenceList->objectName().isEmpty())
            SequenceList->setObjectName("SequenceList");
        SequenceList->resize(240, 34);
        verticalLayout = new QVBoxLayout(SequenceList);
        verticalLayout->setObjectName("verticalLayout");

        retranslateUi(SequenceList);

        QMetaObject::connectSlotsByName(SequenceList);
    } // setupUi

    void retranslateUi(QWidget *SequenceList)
    {
        SequenceList->setWindowTitle(QCoreApplication::translate("SequenceList", "Form", nullptr));
    } // retranslateUi

};

namespace Ui {
    class SequenceList: public Ui_SequenceList {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SEQUENCELIST_H

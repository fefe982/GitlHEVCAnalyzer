/********************************************************************************
** Form generated from reading UI file 'messageviewer.ui'
**
** Created by: Qt User Interface Compiler version 6.8.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MESSAGEVIEWER_H
#define UI_MESSAGEVIEWER_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QTextBrowser>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MessageViewer
{
public:
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout;
    QSpacerItem *horizontalSpacer;
    QCheckBox *debugCheckBox;
    QCheckBox *warningCheckBox;
    QCheckBox *critiCheckBox;
    QCheckBox *fatalCheckBox;
    QPushButton *clearMsgBtn;
    QTextBrowser *msgTextBrowser;

    void setupUi(QWidget *MessageViewer)
    {
        if (MessageViewer->objectName().isEmpty())
            MessageViewer->setObjectName("MessageViewer");
        MessageViewer->resize(336, 196);
        verticalLayout = new QVBoxLayout(MessageViewer);
        verticalLayout->setSpacing(0);
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        verticalLayout->setObjectName("verticalLayout");
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(7);
        horizontalLayout->setObjectName("horizontalLayout");
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        debugCheckBox = new QCheckBox(MessageViewer);
        debugCheckBox->setObjectName("debugCheckBox");
        debugCheckBox->setChecked(true);

        horizontalLayout->addWidget(debugCheckBox);

        warningCheckBox = new QCheckBox(MessageViewer);
        warningCheckBox->setObjectName("warningCheckBox");
        warningCheckBox->setChecked(true);

        horizontalLayout->addWidget(warningCheckBox);

        critiCheckBox = new QCheckBox(MessageViewer);
        critiCheckBox->setObjectName("critiCheckBox");
        critiCheckBox->setChecked(true);

        horizontalLayout->addWidget(critiCheckBox);

        fatalCheckBox = new QCheckBox(MessageViewer);
        fatalCheckBox->setObjectName("fatalCheckBox");
        fatalCheckBox->setChecked(true);

        horizontalLayout->addWidget(fatalCheckBox);

        clearMsgBtn = new QPushButton(MessageViewer);
        clearMsgBtn->setObjectName("clearMsgBtn");

        horizontalLayout->addWidget(clearMsgBtn);


        verticalLayout->addLayout(horizontalLayout);

        msgTextBrowser = new QTextBrowser(MessageViewer);
        msgTextBrowser->setObjectName("msgTextBrowser");

        verticalLayout->addWidget(msgTextBrowser);


        retranslateUi(MessageViewer);

        QMetaObject::connectSlotsByName(MessageViewer);
    } // setupUi

    void retranslateUi(QWidget *MessageViewer)
    {
        MessageViewer->setWindowTitle(QCoreApplication::translate("MessageViewer", "Form", nullptr));
        debugCheckBox->setText(QCoreApplication::translate("MessageViewer", "Debug", nullptr));
        warningCheckBox->setText(QCoreApplication::translate("MessageViewer", "Warning", nullptr));
        critiCheckBox->setText(QCoreApplication::translate("MessageViewer", "Criti", nullptr));
        fatalCheckBox->setText(QCoreApplication::translate("MessageViewer", "Fatal", nullptr));
        clearMsgBtn->setText(QCoreApplication::translate("MessageViewer", "Clear", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MessageViewer: public Ui_MessageViewer {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MESSAGEVIEWER_H

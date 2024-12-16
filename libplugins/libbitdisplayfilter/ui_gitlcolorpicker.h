/********************************************************************************
** Form generated from reading UI file 'gitlcolorpicker.ui'
**
** Created by: Qt User Interface Compiler version 6.8.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_GITLCOLORPICKER_H
#define UI_GITLCOLORPICKER_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_GitlColorPicker
{
public:
    QHBoxLayout *horizontalLayout;
    QPushButton *selectColorBtn;
    QLabel *label;
    QSpacerItem *horizontalSpacer;

    void setupUi(QWidget *GitlColorPicker)
    {
        if (GitlColorPicker->objectName().isEmpty())
            GitlColorPicker->setObjectName("GitlColorPicker");
        GitlColorPicker->resize(164, 26);
        horizontalLayout = new QHBoxLayout(GitlColorPicker);
        horizontalLayout->setObjectName("horizontalLayout");
        horizontalLayout->setContentsMargins(-1, 0, -1, 0);
        selectColorBtn = new QPushButton(GitlColorPicker);
        selectColorBtn->setObjectName("selectColorBtn");
        selectColorBtn->setEnabled(true);

        horizontalLayout->addWidget(selectColorBtn);

        label = new QLabel(GitlColorPicker);
        label->setObjectName("label");

        horizontalLayout->addWidget(label);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);


        retranslateUi(GitlColorPicker);

        QMetaObject::connectSlotsByName(GitlColorPicker);
    } // setupUi

    void retranslateUi(QWidget *GitlColorPicker)
    {
        GitlColorPicker->setWindowTitle(QCoreApplication::translate("GitlColorPicker", "Form", nullptr));
        selectColorBtn->setText(QString());
        label->setText(QCoreApplication::translate("GitlColorPicker", "LABEL", nullptr));
    } // retranslateUi

};

namespace Ui {
    class GitlColorPicker: public Ui_GitlColorPicker {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_GITLCOLORPICKER_H

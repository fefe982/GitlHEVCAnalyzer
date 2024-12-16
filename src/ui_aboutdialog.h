/********************************************************************************
** Form generated from reading UI file 'aboutdialog.ui'
**
** Created by: Qt User Interface Compiler version 6.8.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ABOUTDIALOG_H
#define UI_ABOUTDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_AboutDialog
{
public:
    QVBoxLayout *verticalLayout;
    QLabel *label;
    QHBoxLayout *horizontalLayout;
    QSpacerItem *horizontalSpacer;
    QLabel *label_7;
    QLabel *versionLabel;
    QSpacerItem *horizontalSpacer_2;
    QLabel *label_2;
    QLabel *label_3;
    QLabel *label_8;
    QLabel *label_4;
    QLabel *label_5;
    QLabel *label_6;

    void setupUi(QDialog *AboutDialog)
    {
        if (AboutDialog->objectName().isEmpty())
            AboutDialog->setObjectName("AboutDialog");
        AboutDialog->setWindowModality(Qt::ApplicationModal);
        AboutDialog->resize(433, 245);
        QSizePolicy sizePolicy(QSizePolicy::Policy::Fixed, QSizePolicy::Policy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(AboutDialog->sizePolicy().hasHeightForWidth());
        AboutDialog->setSizePolicy(sizePolicy);
        AboutDialog->setMinimumSize(QSize(433, 245));
        AboutDialog->setMaximumSize(QSize(433, 245));
        verticalLayout = new QVBoxLayout(AboutDialog);
        verticalLayout->setObjectName("verticalLayout");
        label = new QLabel(AboutDialog);
        label->setObjectName("label");
        QFont font;
        font.setPointSize(13);
        font.setBold(true);
        label->setFont(font);
        label->setAlignment(Qt::AlignCenter);

        verticalLayout->addWidget(label);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName("horizontalLayout");
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        label_7 = new QLabel(AboutDialog);
        label_7->setObjectName("label_7");
        label_7->setAlignment(Qt::AlignCenter);

        horizontalLayout->addWidget(label_7);

        versionLabel = new QLabel(AboutDialog);
        versionLabel->setObjectName("versionLabel");
        versionLabel->setAlignment(Qt::AlignCenter);

        horizontalLayout->addWidget(versionLabel);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_2);


        verticalLayout->addLayout(horizontalLayout);

        label_2 = new QLabel(AboutDialog);
        label_2->setObjectName("label_2");
        label_2->setAlignment(Qt::AlignCenter);

        verticalLayout->addWidget(label_2);

        label_3 = new QLabel(AboutDialog);
        label_3->setObjectName("label_3");
        QFont font1;
        font1.setPointSize(11);
        label_3->setFont(font1);
        label_3->setAlignment(Qt::AlignCenter);
        label_3->setOpenExternalLinks(true);

        verticalLayout->addWidget(label_3);

        label_8 = new QLabel(AboutDialog);
        label_8->setObjectName("label_8");
        QFont font2;
        font2.setPointSize(10);
        label_8->setFont(font2);
        label_8->setAlignment(Qt::AlignCenter);
        label_8->setOpenExternalLinks(true);

        verticalLayout->addWidget(label_8);

        label_4 = new QLabel(AboutDialog);
        label_4->setObjectName("label_4");
        label_4->setFont(font2);
        label_4->setAlignment(Qt::AlignCenter);

        verticalLayout->addWidget(label_4);

        label_5 = new QLabel(AboutDialog);
        label_5->setObjectName("label_5");
        label_5->setFont(font2);
        label_5->setAlignment(Qt::AlignCenter);

        verticalLayout->addWidget(label_5);

        label_6 = new QLabel(AboutDialog);
        label_6->setObjectName("label_6");
        label_6->setFont(font2);
        label_6->setAlignment(Qt::AlignCenter);
        label_6->setOpenExternalLinks(true);

        verticalLayout->addWidget(label_6);


        retranslateUi(AboutDialog);

        QMetaObject::connectSlotsByName(AboutDialog);
    } // setupUi

    void retranslateUi(QDialog *AboutDialog)
    {
        AboutDialog->setWindowTitle(QCoreApplication::translate("AboutDialog", "About Gitl HEVC Analyzer", nullptr));
        label->setText(QCoreApplication::translate("AboutDialog", "Gitl HEVC Analyzer", nullptr));
        label_7->setText(QCoreApplication::translate("AboutDialog", "Version", nullptr));
        versionLabel->setText(QCoreApplication::translate("AboutDialog", "xxxx", nullptr));
        label_2->setText(QCoreApplication::translate("AboutDialog", "Copyright(C) 2013", nullptr));
        label_3->setText(QCoreApplication::translate("AboutDialog", "<html><head/><body><p>Author: Huang Li (\346\235\216\347\222\234)</p></body></html>", nullptr));
        label_8->setText(QCoreApplication::translate("AboutDialog", "<html><head/><body><p><a href= \"mailto:lihuang55555@gmail.com\"><span style=\" text-decoration: underline; color:#cacaca;\">Email: lihuang55555@gmail.com</span></a></p></body></html>", nullptr));
        label_4->setText(QCoreApplication::translate("AboutDialog", "Sun Yat-sen University, Guangzhou, P.R.China", nullptr));
        label_5->setText(QCoreApplication::translate("AboutDialog", "<html><head/><body><p><span style=\" font-style:italic;\">Supervised by Prof. Hongyang CHAO (\346\234\235\347\272\242\351\230\263)</span></p></body></html>", nullptr));
        label_6->setText(QCoreApplication::translate("AboutDialog", "<html><head/><body><p><a href=\"mailto:isschhy@mail.sysu.edu.cn\"><span style=\" text-decoration: underline; color:#a7a7a7;\">Email: isschhy@mail.sysu.edu.cn</span></a></p></body></html>", nullptr));
    } // retranslateUi

};

namespace Ui {
    class AboutDialog: public Ui_AboutDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ABOUTDIALOG_H

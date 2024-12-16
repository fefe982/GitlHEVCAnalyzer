/********************************************************************************
** Form generated from reading UI file 'preferencedialog.ui'
**
** Created by: Qt User Interface Compiler version 6.8.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PREFERENCEDIALOG_H
#define UI_PREFERENCEDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QAbstractButton>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_PreferenceDialog
{
public:
    QVBoxLayout *verticalLayout_2;
    QVBoxLayout *verticalLayout;
    QLabel *label;
    QHBoxLayout *horizontalLayout;
    QLineEdit *cacheFolderEdit;
    QPushButton *cacheFolderBrowseBtn;
    QLabel *label_2;
    QDialogButtonBox *buttonBox;

    void setupUi(QDialog *PreferenceDialog)
    {
        if (PreferenceDialog->objectName().isEmpty())
            PreferenceDialog->setObjectName("PreferenceDialog");
        PreferenceDialog->setWindowModality(Qt::ApplicationModal);
        PreferenceDialog->resize(489, 188);
        verticalLayout_2 = new QVBoxLayout(PreferenceDialog);
        verticalLayout_2->setObjectName("verticalLayout_2");
        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName("verticalLayout");
        label = new QLabel(PreferenceDialog);
        label->setObjectName("label");
        label->setWordWrap(true);

        verticalLayout->addWidget(label);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName("horizontalLayout");
        cacheFolderEdit = new QLineEdit(PreferenceDialog);
        cacheFolderEdit->setObjectName("cacheFolderEdit");

        horizontalLayout->addWidget(cacheFolderEdit);

        cacheFolderBrowseBtn = new QPushButton(PreferenceDialog);
        cacheFolderBrowseBtn->setObjectName("cacheFolderBrowseBtn");

        horizontalLayout->addWidget(cacheFolderBrowseBtn);


        verticalLayout->addLayout(horizontalLayout);

        label_2 = new QLabel(PreferenceDialog);
        label_2->setObjectName("label_2");
        label_2->setWordWrap(true);

        verticalLayout->addWidget(label_2);


        verticalLayout_2->addLayout(verticalLayout);

        buttonBox = new QDialogButtonBox(PreferenceDialog);
        buttonBox->setObjectName("buttonBox");
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);

        verticalLayout_2->addWidget(buttonBox);


        retranslateUi(PreferenceDialog);

        QMetaObject::connectSlotsByName(PreferenceDialog);
    } // setupUi

    void retranslateUi(QDialog *PreferenceDialog)
    {
        PreferenceDialog->setWindowTitle(QCoreApplication::translate("PreferenceDialog", "Preferences", nullptr));
        label->setText(QCoreApplication::translate("PreferenceDialog", "Cache Folder:", nullptr));
        cacheFolderBrowseBtn->setText(QCoreApplication::translate("PreferenceDialog", "Browse...", nullptr));
        label_2->setText(QCoreApplication::translate("PreferenceDialog", "* It is where the analyzer writes the temporary files. It should at least have 2 GB free space.", nullptr));
    } // retranslateUi

};

namespace Ui {
    class PreferenceDialog: public Ui_PreferenceDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PREFERENCEDIALOG_H

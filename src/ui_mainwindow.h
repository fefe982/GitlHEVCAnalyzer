/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.8.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDockWidget>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSlider>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QToolButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include "views/frameview.h"
#include "views/messageviewer.h"
#include "views/pluginfilterlist.h"
#include "views/sequencelist.h"
#include "views/timelineview.h"

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *actionOpen_bitstream;
    QAction *actionHelp;
    QAction *actionAbout;
    QAction *actionExit;
    QAction *actionCheckUpdate;
    QAction *actionReloadPluginsFilters;
    QAction *actionPreferences;
    QAction *defaultThemeAction;
    QAction *darkThemeAction;
    QAction *actionTest;
    QWidget *centralwidget;
    QVBoxLayout *verticalLayout_2;
    QWidget *imageWidget;
    QVBoxLayout *verticalLayout;
    FrameView *imageView;
    QWidget *widget;
    QHBoxLayout *horizontalLayout;
    QToolButton *openBitstreamBtn;
    QToolButton *printScreenBtn;
    QSpacerItem *horizontalSpacer_4;
    QToolButton *resetZoomBtn;
    QSpinBox *zoomSpinBox;
    QLabel *resolutionInfoLabel;
    TimeLineView *timelineView;
    QDockWidget *sequencesListDockWidget;
    QWidget *dockWidgetContents_2;
    QVBoxLayout *verticalLayout_3;
    SequenceList *sequenceListWidget;
    QDockWidget *pluginFilterListDockWidget;
    QWidget *dockWidgetContents_3;
    QVBoxLayout *verticalLayout_6;
    PluginFilterList *listWidget;
    QDockWidget *msgDockWidget;
    QWidget *dockWidgetContents_5;
    QVBoxLayout *verticalLayout_5;
    MessageViewer *messageBrowser;
    QDockWidget *playbackDockWidget;
    QWidget *dockWidgetContents_4;
    QVBoxLayout *verticalLayout_7;
    QHBoxLayout *horizontalLayout_7;
    QVBoxLayout *verticalLayout_4;
    QSlider *progressBar;
    QHBoxLayout *horizontalLayout_3;
    QLabel *frame;
    QLabel *currentFrameNum;
    QLabel *label;
    QLabel *totalFrameNum;
    QSpacerItem *horizontalSpacer_3;
    QPushButton *previousFrame;
    QPushButton *nextFrame;
    QMenuBar *menubar;
    QMenu *menuBitstream;
    QMenu *menuHelp;
    QMenu *menuPlugins;
    QMenu *menuOptions;
    QMenu *menuThemes;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(1227, 781);
        QIcon icon;
        icon.addFile(QString::fromUtf8("../../icons/main.ico"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        MainWindow->setWindowIcon(icon);
        MainWindow->setStyleSheet(QString::fromUtf8(""));
        actionOpen_bitstream = new QAction(MainWindow);
        actionOpen_bitstream->setObjectName("actionOpen_bitstream");
        actionHelp = new QAction(MainWindow);
        actionHelp->setObjectName("actionHelp");
        actionAbout = new QAction(MainWindow);
        actionAbout->setObjectName("actionAbout");
        actionExit = new QAction(MainWindow);
        actionExit->setObjectName("actionExit");
        actionCheckUpdate = new QAction(MainWindow);
        actionCheckUpdate->setObjectName("actionCheckUpdate");
        actionCheckUpdate->setEnabled(false);
        actionReloadPluginsFilters = new QAction(MainWindow);
        actionReloadPluginsFilters->setObjectName("actionReloadPluginsFilters");
        actionPreferences = new QAction(MainWindow);
        actionPreferences->setObjectName("actionPreferences");
        defaultThemeAction = new QAction(MainWindow);
        defaultThemeAction->setObjectName("defaultThemeAction");
        defaultThemeAction->setCheckable(true);
        defaultThemeAction->setChecked(true);
        darkThemeAction = new QAction(MainWindow);
        darkThemeAction->setObjectName("darkThemeAction");
        darkThemeAction->setCheckable(true);
        actionTest = new QAction(MainWindow);
        actionTest->setObjectName("actionTest");
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        verticalLayout_2 = new QVBoxLayout(centralwidget);
        verticalLayout_2->setSpacing(1);
        verticalLayout_2->setObjectName("verticalLayout_2");
        imageWidget = new QWidget(centralwidget);
        imageWidget->setObjectName("imageWidget");
        verticalLayout = new QVBoxLayout(imageWidget);
        verticalLayout->setSpacing(0);
        verticalLayout->setObjectName("verticalLayout");
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        imageView = new FrameView(imageWidget);
        imageView->setObjectName("imageView");
        imageView->setStyleSheet(QString::fromUtf8(""));

        verticalLayout->addWidget(imageView);


        verticalLayout_2->addWidget(imageWidget);

        widget = new QWidget(centralwidget);
        widget->setObjectName("widget");
        horizontalLayout = new QHBoxLayout(widget);
        horizontalLayout->setObjectName("horizontalLayout");
        horizontalLayout->setContentsMargins(-1, 0, -1, 0);
        openBitstreamBtn = new QToolButton(widget);
        openBitstreamBtn->setObjectName("openBitstreamBtn");

        horizontalLayout->addWidget(openBitstreamBtn);

        printScreenBtn = new QToolButton(widget);
        printScreenBtn->setObjectName("printScreenBtn");

        horizontalLayout->addWidget(printScreenBtn);

        horizontalSpacer_4 = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_4);

        resetZoomBtn = new QToolButton(widget);
        resetZoomBtn->setObjectName("resetZoomBtn");

        horizontalLayout->addWidget(resetZoomBtn);

        zoomSpinBox = new QSpinBox(widget);
        zoomSpinBox->setObjectName("zoomSpinBox");
        zoomSpinBox->setKeyboardTracking(false);
        zoomSpinBox->setMinimum(10);
        zoomSpinBox->setMaximum(1000);
        zoomSpinBox->setValue(100);

        horizontalLayout->addWidget(zoomSpinBox);

        resolutionInfoLabel = new QLabel(widget);
        resolutionInfoLabel->setObjectName("resolutionInfoLabel");

        horizontalLayout->addWidget(resolutionInfoLabel);


        verticalLayout_2->addWidget(widget);

        timelineView = new TimeLineView(centralwidget);
        timelineView->setObjectName("timelineView");
        QSizePolicy sizePolicy(QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(timelineView->sizePolicy().hasHeightForWidth());
        timelineView->setSizePolicy(sizePolicy);
        timelineView->setMinimumSize(QSize(0, 180));
        timelineView->setMaximumSize(QSize(16777215, 180));

        verticalLayout_2->addWidget(timelineView);

        MainWindow->setCentralWidget(centralwidget);
        sequencesListDockWidget = new QDockWidget(MainWindow);
        sequencesListDockWidget->setObjectName("sequencesListDockWidget");
        sequencesListDockWidget->setStyleSheet(QString::fromUtf8(""));
        sequencesListDockWidget->setFloating(false);
        sequencesListDockWidget->setFeatures(QDockWidget::DockWidgetFloatable|QDockWidget::DockWidgetMovable);
        dockWidgetContents_2 = new QWidget();
        dockWidgetContents_2->setObjectName("dockWidgetContents_2");
        verticalLayout_3 = new QVBoxLayout(dockWidgetContents_2);
        verticalLayout_3->setObjectName("verticalLayout_3");
        sequenceListWidget = new SequenceList(dockWidgetContents_2);
        sequenceListWidget->setObjectName("sequenceListWidget");

        verticalLayout_3->addWidget(sequenceListWidget);

        sequencesListDockWidget->setWidget(dockWidgetContents_2);
        MainWindow->addDockWidget(Qt::DockWidgetArea::LeftDockWidgetArea, sequencesListDockWidget);
        pluginFilterListDockWidget = new QDockWidget(MainWindow);
        pluginFilterListDockWidget->setObjectName("pluginFilterListDockWidget");
        QSizePolicy sizePolicy1(QSizePolicy::Policy::Preferred, QSizePolicy::Policy::Minimum);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(pluginFilterListDockWidget->sizePolicy().hasHeightForWidth());
        pluginFilterListDockWidget->setSizePolicy(sizePolicy1);
        pluginFilterListDockWidget->setStyleSheet(QString::fromUtf8(""));
        pluginFilterListDockWidget->setFeatures(QDockWidget::DockWidgetFloatable|QDockWidget::DockWidgetMovable);
        dockWidgetContents_3 = new QWidget();
        dockWidgetContents_3->setObjectName("dockWidgetContents_3");
        verticalLayout_6 = new QVBoxLayout(dockWidgetContents_3);
        verticalLayout_6->setObjectName("verticalLayout_6");
        listWidget = new PluginFilterList(dockWidgetContents_3);
        listWidget->setObjectName("listWidget");

        verticalLayout_6->addWidget(listWidget);

        pluginFilterListDockWidget->setWidget(dockWidgetContents_3);
        MainWindow->addDockWidget(Qt::DockWidgetArea::LeftDockWidgetArea, pluginFilterListDockWidget);
        msgDockWidget = new QDockWidget(MainWindow);
        msgDockWidget->setObjectName("msgDockWidget");
        QSizePolicy sizePolicy2(QSizePolicy::Policy::Preferred, QSizePolicy::Policy::Maximum);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(msgDockWidget->sizePolicy().hasHeightForWidth());
        msgDockWidget->setSizePolicy(sizePolicy2);
        msgDockWidget->setFeatures(QDockWidget::DockWidgetFloatable|QDockWidget::DockWidgetMovable);
        dockWidgetContents_5 = new QWidget();
        dockWidgetContents_5->setObjectName("dockWidgetContents_5");
        verticalLayout_5 = new QVBoxLayout(dockWidgetContents_5);
        verticalLayout_5->setObjectName("verticalLayout_5");
        messageBrowser = new MessageViewer(dockWidgetContents_5);
        messageBrowser->setObjectName("messageBrowser");

        verticalLayout_5->addWidget(messageBrowser);

        msgDockWidget->setWidget(dockWidgetContents_5);
        MainWindow->addDockWidget(Qt::DockWidgetArea::LeftDockWidgetArea, msgDockWidget);
        playbackDockWidget = new QDockWidget(MainWindow);
        playbackDockWidget->setObjectName("playbackDockWidget");
        playbackDockWidget->setFeatures(QDockWidget::DockWidgetFloatable|QDockWidget::DockWidgetMovable);
        dockWidgetContents_4 = new QWidget();
        dockWidgetContents_4->setObjectName("dockWidgetContents_4");
        verticalLayout_7 = new QVBoxLayout(dockWidgetContents_4);
        verticalLayout_7->setObjectName("verticalLayout_7");
        horizontalLayout_7 = new QHBoxLayout();
        horizontalLayout_7->setObjectName("horizontalLayout_7");
        horizontalLayout_7->setContentsMargins(-1, -1, -1, 0);
        verticalLayout_4 = new QVBoxLayout();
        verticalLayout_4->setObjectName("verticalLayout_4");
        progressBar = new QSlider(dockWidgetContents_4);
        progressBar->setObjectName("progressBar");
        progressBar->setMinimumSize(QSize(0, 20));
        progressBar->setMouseTracking(true);
        progressBar->setPageStep(1);
        progressBar->setOrientation(Qt::Horizontal);

        verticalLayout_4->addWidget(progressBar);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setSpacing(0);
        horizontalLayout_3->setObjectName("horizontalLayout_3");
        frame = new QLabel(dockWidgetContents_4);
        frame->setObjectName("frame");
        QSizePolicy sizePolicy3(QSizePolicy::Policy::Fixed, QSizePolicy::Policy::Preferred);
        sizePolicy3.setHorizontalStretch(0);
        sizePolicy3.setVerticalStretch(0);
        sizePolicy3.setHeightForWidth(frame->sizePolicy().hasHeightForWidth());
        frame->setSizePolicy(sizePolicy3);
        frame->setMargin(1);

        horizontalLayout_3->addWidget(frame);

        currentFrameNum = new QLabel(dockWidgetContents_4);
        currentFrameNum->setObjectName("currentFrameNum");
        sizePolicy3.setHeightForWidth(currentFrameNum->sizePolicy().hasHeightForWidth());
        currentFrameNum->setSizePolicy(sizePolicy3);
        currentFrameNum->setMinimumSize(QSize(20, 0));
        currentFrameNum->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        horizontalLayout_3->addWidget(currentFrameNum);

        label = new QLabel(dockWidgetContents_4);
        label->setObjectName("label");
        sizePolicy3.setHeightForWidth(label->sizePolicy().hasHeightForWidth());
        label->setSizePolicy(sizePolicy3);

        horizontalLayout_3->addWidget(label);

        totalFrameNum = new QLabel(dockWidgetContents_4);
        totalFrameNum->setObjectName("totalFrameNum");
        sizePolicy3.setHeightForWidth(totalFrameNum->sizePolicy().hasHeightForWidth());
        totalFrameNum->setSizePolicy(sizePolicy3);
        totalFrameNum->setMinimumSize(QSize(30, 0));
        totalFrameNum->setMargin(5);

        horizontalLayout_3->addWidget(totalFrameNum);

        horizontalSpacer_3 = new QSpacerItem(0, 0, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer_3);

        previousFrame = new QPushButton(dockWidgetContents_4);
        previousFrame->setObjectName("previousFrame");

        horizontalLayout_3->addWidget(previousFrame);

        nextFrame = new QPushButton(dockWidgetContents_4);
        nextFrame->setObjectName("nextFrame");
        QSizePolicy sizePolicy4(QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Fixed);
        sizePolicy4.setHorizontalStretch(0);
        sizePolicy4.setVerticalStretch(0);
        sizePolicy4.setHeightForWidth(nextFrame->sizePolicy().hasHeightForWidth());
        nextFrame->setSizePolicy(sizePolicy4);

        horizontalLayout_3->addWidget(nextFrame);


        verticalLayout_4->addLayout(horizontalLayout_3);


        horizontalLayout_7->addLayout(verticalLayout_4);


        verticalLayout_7->addLayout(horizontalLayout_7);

        playbackDockWidget->setWidget(dockWidgetContents_4);
        MainWindow->addDockWidget(Qt::DockWidgetArea::LeftDockWidgetArea, playbackDockWidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 1227, 23));
        menubar->setNativeMenuBar(false);
        menuBitstream = new QMenu(menubar);
        menuBitstream->setObjectName("menuBitstream");
        menuHelp = new QMenu(menubar);
        menuHelp->setObjectName("menuHelp");
        menuPlugins = new QMenu(menubar);
        menuPlugins->setObjectName("menuPlugins");
        menuOptions = new QMenu(menubar);
        menuOptions->setObjectName("menuOptions");
        menuThemes = new QMenu(menuOptions);
        menuThemes->setObjectName("menuThemes");
        MainWindow->setMenuBar(menubar);

        menubar->addAction(menuBitstream->menuAction());
        menubar->addAction(menuPlugins->menuAction());
        menubar->addAction(menuOptions->menuAction());
        menubar->addAction(menuHelp->menuAction());
        menuBitstream->addAction(actionOpen_bitstream);
        menuBitstream->addSeparator();
        menuBitstream->addAction(actionExit);
        menuHelp->addAction(actionCheckUpdate);
        menuHelp->addAction(actionHelp);
        menuHelp->addAction(actionAbout);
        menuPlugins->addAction(actionReloadPluginsFilters);
        menuOptions->addAction(actionPreferences);
        menuOptions->addAction(menuThemes->menuAction());
        menuThemes->addAction(defaultThemeAction);
        menuThemes->addAction(darkThemeAction);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "Gitl HEVC Analyzer", nullptr));
        actionOpen_bitstream->setText(QCoreApplication::translate("MainWindow", "Open HEVC Bitstream", nullptr));
        actionHelp->setText(QCoreApplication::translate("MainWindow", "Online Manual", nullptr));
        actionAbout->setText(QCoreApplication::translate("MainWindow", "About", nullptr));
        actionExit->setText(QCoreApplication::translate("MainWindow", "Exit", nullptr));
        actionCheckUpdate->setText(QCoreApplication::translate("MainWindow", "Check for update", nullptr));
        actionReloadPluginsFilters->setText(QCoreApplication::translate("MainWindow", "Reload Plugins Filters", nullptr));
        actionPreferences->setText(QCoreApplication::translate("MainWindow", "Preferences", nullptr));
        defaultThemeAction->setText(QCoreApplication::translate("MainWindow", "Default", nullptr));
        darkThemeAction->setText(QCoreApplication::translate("MainWindow", "Dark", nullptr));
        actionTest->setText(QCoreApplication::translate("MainWindow", "test", nullptr));
        openBitstreamBtn->setText(QCoreApplication::translate("MainWindow", "Open", nullptr));
        printScreenBtn->setText(QCoreApplication::translate("MainWindow", "Snapshot", nullptr));
#if QT_CONFIG(whatsthis)
        resetZoomBtn->setWhatsThis(QCoreApplication::translate("MainWindow", "Zooming Reset", nullptr));
#endif // QT_CONFIG(whatsthis)
        resetZoomBtn->setText(QCoreApplication::translate("MainWindow", "Reset", nullptr));
        zoomSpinBox->setSuffix(QCoreApplication::translate("MainWindow", "%", nullptr));
        resolutionInfoLabel->setText(QCoreApplication::translate("MainWindow", "---X---", nullptr));
        sequencesListDockWidget->setWindowTitle(QCoreApplication::translate("MainWindow", "Sequence List", nullptr));
        pluginFilterListDockWidget->setWindowTitle(QCoreApplication::translate("MainWindow", "Plugin Filter List", nullptr));
        msgDockWidget->setWindowTitle(QCoreApplication::translate("MainWindow", "Message Output", nullptr));
        playbackDockWidget->setWindowTitle(QCoreApplication::translate("MainWindow", "Playback Control", nullptr));
        frame->setText(QCoreApplication::translate("MainWindow", " Frame", nullptr));
        currentFrameNum->setText(QCoreApplication::translate("MainWindow", " 0", nullptr));
        label->setText(QCoreApplication::translate("MainWindow", " /", nullptr));
        totalFrameNum->setText(QCoreApplication::translate("MainWindow", "0", nullptr));
        previousFrame->setText(QCoreApplication::translate("MainWindow", " < ", nullptr));
        nextFrame->setText(QCoreApplication::translate("MainWindow", " > ", nullptr));
        menuBitstream->setTitle(QCoreApplication::translate("MainWindow", "FILE", nullptr));
        menuHelp->setTitle(QCoreApplication::translate("MainWindow", "HELP", nullptr));
        menuPlugins->setTitle(QCoreApplication::translate("MainWindow", "PLGINS", nullptr));
        menuOptions->setTitle(QCoreApplication::translate("MainWindow", "OPTIONS", nullptr));
        menuThemes->setTitle(QCoreApplication::translate("MainWindow", "Themes", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H

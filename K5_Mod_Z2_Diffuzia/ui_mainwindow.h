/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.7.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSlider>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QWidget>
#include "QtCharts"
#include "glscene.h"
#include "qcustomplot.h"

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralWidget;
    QTabWidget *tabWidget;
    QWidget *tab;
    glScene *Scene_widget;
    QPushButton *pushButton_GenStart;
    QPushButton *pushButton;
    QTextEdit *textEdit_ForStep;
    QSpinBox *spinBox_MC_StepsCount;
    QPushButton *pushButton_Animation;
    QLabel *label;
    QLabel *label_2;
    QPushButton *pushButton_GenStart_1000;
    QPushButton *pushButton_GenStart_Ogran;
    QWidget *tab_2;
    QSlider *horizontalSlider;
    QCustomPlot *widget;
    QPushButton *pushButton_Concentration;
    QChartViewer *graphicsView;
    QSlider *horizontalSlider_2;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(1279, 733);
        MainWindow->setAutoFillBackground(false);
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        tabWidget = new QTabWidget(centralWidget);
        tabWidget->setObjectName(QStringLiteral("tabWidget"));
        tabWidget->setGeometry(QRect(0, 0, 1261, 721));
        tab = new QWidget();
        tab->setObjectName(QStringLiteral("tab"));
        Scene_widget = new glScene(tab);
        Scene_widget->setObjectName(QStringLiteral("Scene_widget"));
        Scene_widget->setGeometry(QRect(10, 10, 1200, 600));
        Scene_widget->setStyleSheet(QStringLiteral(""));
        pushButton_GenStart = new QPushButton(tab);
        pushButton_GenStart->setObjectName(QStringLiteral("pushButton_GenStart"));
        pushButton_GenStart->setGeometry(QRect(210, 630, 111, 31));
        pushButton = new QPushButton(tab);
        pushButton->setObjectName(QStringLiteral("pushButton"));
        pushButton->setGeometry(QRect(330, 630, 111, 31));
        textEdit_ForStep = new QTextEdit(tab);
        textEdit_ForStep->setObjectName(QStringLiteral("textEdit_ForStep"));
        textEdit_ForStep->setGeometry(QRect(670, 630, 71, 31));
        spinBox_MC_StepsCount = new QSpinBox(tab);
        spinBox_MC_StepsCount->setObjectName(QStringLiteral("spinBox_MC_StepsCount"));
        spinBox_MC_StepsCount->setGeometry(QRect(120, 630, 71, 31));
        spinBox_MC_StepsCount->setMaximum(7000);
        spinBox_MC_StepsCount->setSingleStep(100);
        spinBox_MC_StepsCount->setValue(500);
        pushButton_Animation = new QPushButton(tab);
        pushButton_Animation->setObjectName(QStringLiteral("pushButton_Animation"));
        pushButton_Animation->setGeometry(QRect(450, 630, 111, 31));
        label = new QLabel(tab);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(10, 640, 101, 16));
        label->setFrameShape(QFrame::NoFrame);
        label_2 = new QLabel(tab);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setGeometry(QRect(600, 640, 71, 16));
        label_2->setFrameShape(QFrame::NoFrame);
        pushButton_GenStart_1000 = new QPushButton(tab);
        pushButton_GenStart_1000->setObjectName(QStringLiteral("pushButton_GenStart_1000"));
        pushButton_GenStart_1000->setGeometry(QRect(890, 630, 111, 31));
        pushButton_GenStart_Ogran = new QPushButton(tab);
        pushButton_GenStart_Ogran->setObjectName(QStringLiteral("pushButton_GenStart_Ogran"));
        pushButton_GenStart_Ogran->setGeometry(QRect(1040, 630, 121, 31));
        tabWidget->addTab(tab, QString());
        tab_2 = new QWidget();
        tab_2->setObjectName(QStringLiteral("tab_2"));
        horizontalSlider = new QSlider(tab_2);
        horizontalSlider->setObjectName(QStringLiteral("horizontalSlider"));
        horizontalSlider->setGeometry(QRect(20, 310, 621, 19));
        horizontalSlider->setOrientation(Qt::Horizontal);
        widget = new QCustomPlot(tab_2);
        widget->setObjectName(QStringLiteral("widget"));
        widget->setGeometry(QRect(20, 20, 621, 251));
        pushButton_Concentration = new QPushButton(tab_2);
        pushButton_Concentration->setObjectName(QStringLiteral("pushButton_Concentration"));
        pushButton_Concentration->setGeometry(QRect(970, 390, 75, 23));
        graphicsView = new QChartViewer(tab_2);
        graphicsView->setObjectName(QStringLiteral("graphicsView"));
        graphicsView->setGeometry(QRect(680, 10, 550, 350));
        graphicsView->setStyleSheet(QStringLiteral("background-color: rgb(255, 255, 255);"));
        graphicsView->setLineWidth(1);
        horizontalSlider_2 = new QSlider(tab_2);
        horizontalSlider_2->setObjectName(QStringLiteral("horizontalSlider_2"));
        horizontalSlider_2->setGeometry(QRect(700, 440, 481, 19));
        horizontalSlider_2->setMaximum(180);
        horizontalSlider_2->setValue(99);
        horizontalSlider_2->setOrientation(Qt::Horizontal);
        tabWidget->addTab(tab_2, QString());
        MainWindow->setCentralWidget(centralWidget);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        MainWindow->setStatusBar(statusBar);

        retranslateUi(MainWindow);

        tabWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", 0));
        pushButton_GenStart->setText(QApplication::translate("MainWindow", "Generate Start", 0));
        pushButton->setText(QApplication::translate("MainWindow", "Monte-Carlo Step", 0));
        pushButton_Animation->setText(QApplication::translate("MainWindow", "Diffuzia Start/Stop ", 0));
        label->setText(QApplication::translate("MainWindow", "Count of M-C Steps:", 0));
        label_2->setText(QApplication::translate("MainWindow", "Current step:", 0));
        pushButton_GenStart_1000->setText(QApplication::translate("MainWindow", "Generate Start 1000", 0));
        pushButton_GenStart_Ogran->setText(QApplication::translate("MainWindow", "Generate Finit Source", 0));
        tabWidget->setTabText(tabWidget->indexOf(tab), QApplication::translate("MainWindow", "Tab 1", 0));
        pushButton_Concentration->setText(QApplication::translate("MainWindow", "PushButton", 0));
        tabWidget->setTabText(tabWidget->indexOf(tab_2), QApplication::translate("MainWindow", "Tab 2", 0));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H

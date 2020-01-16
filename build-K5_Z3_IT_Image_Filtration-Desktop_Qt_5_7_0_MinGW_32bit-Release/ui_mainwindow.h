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
#include <QtWidgets/QDoubleSpinBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QWidget>
#include "qcustomplot.h"

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralWidget;
    QLabel *label_Img1;
    QPushButton *pushButton_Gen_Image;
    QLabel *label_3;
    QDoubleSpinBox *doubleSpinBox_A2;
    QLabel *label_2;
    QLabel *label_5;
    QDoubleSpinBox *doubleSpinBox_Y01;
    QDoubleSpinBox *doubleSpinBox_A1;
    QLabel *label_8;
    QLabel *label_13;
    QDoubleSpinBox *doubleSpinBox_Y03;
    QDoubleSpinBox *doubleSpinBox_SigmaY2;
    QDoubleSpinBox *doubleSpinBox_SigmaY3;
    QLabel *label_7;
    QLabel *label_12;
    QLabel *label_6;
    QDoubleSpinBox *doubleSpinBox_SigmaX1;
    QLabel *label_11;
    QLabel *label_16;
    QLabel *label_9;
    QLabel *label_14;
    QDoubleSpinBox *doubleSpinBox_Y02;
    QDoubleSpinBox *doubleSpinBox_A3;
    QLabel *label_10;
    QLabel *label_15;
    QDoubleSpinBox *doubleSpinBox_X01;
    QLabel *label_4;
    QDoubleSpinBox *doubleSpinBox_SigmaY1;
    QDoubleSpinBox *doubleSpinBox_X02;
    QDoubleSpinBox *doubleSpinBox_X03;
    QDoubleSpinBox *doubleSpinBox_SigmaX2;
    QDoubleSpinBox *doubleSpinBox_SigmaX3;
    QLabel *label_Img2;
    QDoubleSpinBox *doubleSpinBox_alpha;
    QLabel *label;
    QLabel *label_Vual;
    QTextEdit *textEdit_eps_orig_vual;
    QLabel *label_18;
    QTextEdit *textEdit_eps_orig_filtered;
    QLabel *label_19;
    QPushButton *pushButton_MedFilter_2;
    QSpinBox *spinBox_N;
    QLabel *label_20;
    QPushButton *pushButton_LinFilter_2;
    QPushButton *pushButton_LinFilter_3;
    QLabel *label_ImgMinus;
    QPushButton *pushButton;
    QLabel *label_22;
    QDoubleSpinBox *doubleSpinBox_mu;
    QTextEdit *textEdit_Contraste_ImgPlusVual;
    QLabel *label_23;
    QLabel *label_24;
    QTextEdit *textEdit_Contraste_Restored;
    QPushButton *pushButton_IncreaseBrightness;
    QDoubleSpinBox *doubleSpinBox_k;
    QDoubleSpinBox *doubleSpinBox_b;
    QLabel *label_25;
    QLabel *label_26;
    QLabel *label_27;
    QTextEdit *textEdit_Contraste_Orig;
    QTextEdit *textEdit_Difference_Contraste;
    QLabel *label_28;
    QCustomPlot *widget;
    QPushButton *pushButton_analise;
    QMenuBar *menuBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(1302, 736);
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        label_Img1 = new QLabel(centralWidget);
        label_Img1->setObjectName(QStringLiteral("label_Img1"));
        label_Img1->setGeometry(QRect(40, 20, 256, 256));
        label_Img1->setFrameShape(QFrame::Box);
        label_Img1->setFrameShadow(QFrame::Plain);
        label_Img1->setLineWidth(1);
        pushButton_Gen_Image = new QPushButton(centralWidget);
        pushButton_Gen_Image->setObjectName(QStringLiteral("pushButton_Gen_Image"));
        pushButton_Gen_Image->setGeometry(QRect(1070, 80, 81, 31));
        label_3 = new QLabel(centralWidget);
        label_3->setObjectName(QStringLiteral("label_3"));
        label_3->setGeometry(QRect(700, 60, 21, 20));
        doubleSpinBox_A2 = new QDoubleSpinBox(centralWidget);
        doubleSpinBox_A2->setObjectName(QStringLiteral("doubleSpinBox_A2"));
        doubleSpinBox_A2->setGeometry(QRect(840, 40, 62, 22));
        doubleSpinBox_A2->setMaximum(100);
        doubleSpinBox_A2->setValue(1);
        label_2 = new QLabel(centralWidget);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setGeometry(QRect(700, 40, 16, 16));
        label_5 = new QLabel(centralWidget);
        label_5->setObjectName(QStringLiteral("label_5"));
        label_5->setGeometry(QRect(670, 100, 51, 20));
        doubleSpinBox_Y01 = new QDoubleSpinBox(centralWidget);
        doubleSpinBox_Y01->setObjectName(QStringLiteral("doubleSpinBox_Y01"));
        doubleSpinBox_Y01->setGeometry(QRect(720, 80, 62, 22));
        doubleSpinBox_Y01->setMaximum(1000);
        doubleSpinBox_Y01->setSingleStep(10);
        doubleSpinBox_Y01->setValue(100);
        doubleSpinBox_A1 = new QDoubleSpinBox(centralWidget);
        doubleSpinBox_A1->setObjectName(QStringLiteral("doubleSpinBox_A1"));
        doubleSpinBox_A1->setGeometry(QRect(720, 40, 62, 22));
        doubleSpinBox_A1->setMaximum(100);
        doubleSpinBox_A1->setValue(1);
        label_8 = new QLabel(centralWidget);
        label_8->setObjectName(QStringLiteral("label_8"));
        label_8->setGeometry(QRect(790, 100, 51, 20));
        label_13 = new QLabel(centralWidget);
        label_13->setObjectName(QStringLiteral("label_13"));
        label_13->setGeometry(QRect(910, 100, 51, 20));
        doubleSpinBox_Y03 = new QDoubleSpinBox(centralWidget);
        doubleSpinBox_Y03->setObjectName(QStringLiteral("doubleSpinBox_Y03"));
        doubleSpinBox_Y03->setGeometry(QRect(960, 80, 62, 22));
        doubleSpinBox_Y03->setMaximum(1000);
        doubleSpinBox_Y03->setValue(300);
        doubleSpinBox_SigmaY2 = new QDoubleSpinBox(centralWidget);
        doubleSpinBox_SigmaY2->setObjectName(QStringLiteral("doubleSpinBox_SigmaY2"));
        doubleSpinBox_SigmaY2->setGeometry(QRect(840, 120, 62, 22));
        doubleSpinBox_SigmaY2->setMaximum(300);
        doubleSpinBox_SigmaY2->setSingleStep(10);
        doubleSpinBox_SigmaY2->setValue(60);
        doubleSpinBox_SigmaY3 = new QDoubleSpinBox(centralWidget);
        doubleSpinBox_SigmaY3->setObjectName(QStringLiteral("doubleSpinBox_SigmaY3"));
        doubleSpinBox_SigmaY3->setGeometry(QRect(960, 120, 62, 22));
        doubleSpinBox_SigmaY3->setMaximum(300);
        doubleSpinBox_SigmaY3->setSingleStep(10);
        doubleSpinBox_SigmaY3->setValue(90);
        label_7 = new QLabel(centralWidget);
        label_7->setObjectName(QStringLiteral("label_7"));
        label_7->setGeometry(QRect(820, 60, 21, 20));
        label_12 = new QLabel(centralWidget);
        label_12->setObjectName(QStringLiteral("label_12"));
        label_12->setGeometry(QRect(940, 60, 21, 20));
        label_6 = new QLabel(centralWidget);
        label_6->setObjectName(QStringLiteral("label_6"));
        label_6->setGeometry(QRect(670, 120, 51, 20));
        doubleSpinBox_SigmaX1 = new QDoubleSpinBox(centralWidget);
        doubleSpinBox_SigmaX1->setObjectName(QStringLiteral("doubleSpinBox_SigmaX1"));
        doubleSpinBox_SigmaX1->setGeometry(QRect(720, 100, 62, 22));
        doubleSpinBox_SigmaX1->setMaximum(300);
        doubleSpinBox_SigmaX1->setSingleStep(10);
        doubleSpinBox_SigmaX1->setValue(90);
        label_11 = new QLabel(centralWidget);
        label_11->setObjectName(QStringLiteral("label_11"));
        label_11->setGeometry(QRect(820, 80, 21, 20));
        label_16 = new QLabel(centralWidget);
        label_16->setObjectName(QStringLiteral("label_16"));
        label_16->setGeometry(QRect(940, 80, 21, 20));
        label_9 = new QLabel(centralWidget);
        label_9->setObjectName(QStringLiteral("label_9"));
        label_9->setGeometry(QRect(790, 120, 51, 20));
        label_14 = new QLabel(centralWidget);
        label_14->setObjectName(QStringLiteral("label_14"));
        label_14->setGeometry(QRect(910, 120, 51, 20));
        doubleSpinBox_Y02 = new QDoubleSpinBox(centralWidget);
        doubleSpinBox_Y02->setObjectName(QStringLiteral("doubleSpinBox_Y02"));
        doubleSpinBox_Y02->setGeometry(QRect(840, 80, 62, 22));
        doubleSpinBox_Y02->setMaximum(1000);
        doubleSpinBox_Y02->setValue(320);
        doubleSpinBox_A3 = new QDoubleSpinBox(centralWidget);
        doubleSpinBox_A3->setObjectName(QStringLiteral("doubleSpinBox_A3"));
        doubleSpinBox_A3->setGeometry(QRect(960, 40, 62, 22));
        doubleSpinBox_A3->setMaximum(100);
        doubleSpinBox_A3->setValue(1);
        label_10 = new QLabel(centralWidget);
        label_10->setObjectName(QStringLiteral("label_10"));
        label_10->setGeometry(QRect(820, 40, 16, 16));
        label_15 = new QLabel(centralWidget);
        label_15->setObjectName(QStringLiteral("label_15"));
        label_15->setGeometry(QRect(940, 40, 16, 16));
        doubleSpinBox_X01 = new QDoubleSpinBox(centralWidget);
        doubleSpinBox_X01->setObjectName(QStringLiteral("doubleSpinBox_X01"));
        doubleSpinBox_X01->setGeometry(QRect(720, 60, 62, 22));
        doubleSpinBox_X01->setDecimals(0);
        doubleSpinBox_X01->setMaximum(1000);
        doubleSpinBox_X01->setSingleStep(10);
        doubleSpinBox_X01->setValue(100);
        label_4 = new QLabel(centralWidget);
        label_4->setObjectName(QStringLiteral("label_4"));
        label_4->setGeometry(QRect(700, 80, 21, 20));
        doubleSpinBox_SigmaY1 = new QDoubleSpinBox(centralWidget);
        doubleSpinBox_SigmaY1->setObjectName(QStringLiteral("doubleSpinBox_SigmaY1"));
        doubleSpinBox_SigmaY1->setGeometry(QRect(720, 120, 62, 22));
        doubleSpinBox_SigmaY1->setMaximum(300);
        doubleSpinBox_SigmaY1->setSingleStep(10);
        doubleSpinBox_SigmaY1->setValue(90);
        doubleSpinBox_X02 = new QDoubleSpinBox(centralWidget);
        doubleSpinBox_X02->setObjectName(QStringLiteral("doubleSpinBox_X02"));
        doubleSpinBox_X02->setGeometry(QRect(840, 60, 62, 22));
        doubleSpinBox_X02->setMaximum(1000);
        doubleSpinBox_X02->setValue(290);
        doubleSpinBox_X03 = new QDoubleSpinBox(centralWidget);
        doubleSpinBox_X03->setObjectName(QStringLiteral("doubleSpinBox_X03"));
        doubleSpinBox_X03->setGeometry(QRect(960, 60, 62, 22));
        doubleSpinBox_X03->setMaximum(1000);
        doubleSpinBox_X03->setValue(70);
        doubleSpinBox_SigmaX2 = new QDoubleSpinBox(centralWidget);
        doubleSpinBox_SigmaX2->setObjectName(QStringLiteral("doubleSpinBox_SigmaX2"));
        doubleSpinBox_SigmaX2->setGeometry(QRect(840, 100, 62, 22));
        doubleSpinBox_SigmaX2->setMaximum(300);
        doubleSpinBox_SigmaX2->setSingleStep(10);
        doubleSpinBox_SigmaX2->setValue(60);
        doubleSpinBox_SigmaX3 = new QDoubleSpinBox(centralWidget);
        doubleSpinBox_SigmaX3->setObjectName(QStringLiteral("doubleSpinBox_SigmaX3"));
        doubleSpinBox_SigmaX3->setGeometry(QRect(960, 100, 62, 22));
        doubleSpinBox_SigmaX3->setMaximum(300);
        doubleSpinBox_SigmaX3->setSingleStep(10);
        doubleSpinBox_SigmaX3->setValue(60);
        label_Img2 = new QLabel(centralWidget);
        label_Img2->setObjectName(QStringLiteral("label_Img2"));
        label_Img2->setGeometry(QRect(40, 280, 256, 256));
        label_Img2->setFrameShape(QFrame::Box);
        label_Img2->setFrameShadow(QFrame::Plain);
        label_Img2->setLineWidth(1);
        doubleSpinBox_alpha = new QDoubleSpinBox(centralWidget);
        doubleSpinBox_alpha->setObjectName(QStringLiteral("doubleSpinBox_alpha"));
        doubleSpinBox_alpha->setGeometry(QRect(710, 10, 62, 22));
        doubleSpinBox_alpha->setSingleStep(0.05);
        doubleSpinBox_alpha->setValue(0.35);
        label = new QLabel(centralWidget);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(680, 10, 31, 16));
        label_Vual = new QLabel(centralWidget);
        label_Vual->setObjectName(QStringLiteral("label_Vual"));
        label_Vual->setGeometry(QRect(300, 20, 256, 256));
        label_Vual->setFrameShape(QFrame::Box);
        label_Vual->setFrameShadow(QFrame::Plain);
        label_Vual->setLineWidth(1);
        textEdit_eps_orig_vual = new QTextEdit(centralWidget);
        textEdit_eps_orig_vual->setObjectName(QStringLiteral("textEdit_eps_orig_vual"));
        textEdit_eps_orig_vual->setGeometry(QRect(800, 160, 104, 31));
        label_18 = new QLabel(centralWidget);
        label_18->setObjectName(QStringLiteral("label_18"));
        label_18->setGeometry(QRect(670, 170, 121, 16));
        textEdit_eps_orig_filtered = new QTextEdit(centralWidget);
        textEdit_eps_orig_filtered->setObjectName(QStringLiteral("textEdit_eps_orig_filtered"));
        textEdit_eps_orig_filtered->setGeometry(QRect(800, 190, 104, 31));
        label_19 = new QLabel(centralWidget);
        label_19->setObjectName(QStringLiteral("label_19"));
        label_19->setGeometry(QRect(660, 200, 141, 16));
        pushButton_MedFilter_2 = new QPushButton(centralWidget);
        pushButton_MedFilter_2->setObjectName(QStringLiteral("pushButton_MedFilter_2"));
        pushButton_MedFilter_2->setGeometry(QRect(1070, 220, 111, 23));
        spinBox_N = new QSpinBox(centralWidget);
        spinBox_N->setObjectName(QStringLiteral("spinBox_N"));
        spinBox_N->setGeometry(QRect(1100, 180, 42, 22));
        spinBox_N->setMinimum(3);
        spinBox_N->setSingleStep(2);
        spinBox_N->setValue(3);
        label_20 = new QLabel(centralWidget);
        label_20->setObjectName(QStringLiteral("label_20"));
        label_20->setGeometry(QRect(1045, 180, 51, 20));
        pushButton_LinFilter_2 = new QPushButton(centralWidget);
        pushButton_LinFilter_2->setObjectName(QStringLiteral("pushButton_LinFilter_2"));
        pushButton_LinFilter_2->setGeometry(QRect(1070, 250, 111, 23));
        pushButton_LinFilter_3 = new QPushButton(centralWidget);
        pushButton_LinFilter_3->setObjectName(QStringLiteral("pushButton_LinFilter_3"));
        pushButton_LinFilter_3->setGeometry(QRect(1070, 280, 131, 23));
        label_ImgMinus = new QLabel(centralWidget);
        label_ImgMinus->setObjectName(QStringLiteral("label_ImgMinus"));
        label_ImgMinus->setGeometry(QRect(300, 280, 256, 256));
        label_ImgMinus->setFrameShape(QFrame::Box);
        label_ImgMinus->setFrameShadow(QFrame::Plain);
        label_ImgMinus->setLineWidth(1);
        pushButton = new QPushButton(centralWidget);
        pushButton->setObjectName(QStringLiteral("pushButton"));
        pushButton->setGeometry(QRect(660, 270, 91, 23));
        label_22 = new QLabel(centralWidget);
        label_22->setObjectName(QStringLiteral("label_22"));
        label_22->setGeometry(QRect(670, 240, 21, 16));
        doubleSpinBox_mu = new QDoubleSpinBox(centralWidget);
        doubleSpinBox_mu->setObjectName(QStringLiteral("doubleSpinBox_mu"));
        doubleSpinBox_mu->setGeometry(QRect(690, 240, 61, 22));
        doubleSpinBox_mu->setSingleStep(0.05);
        doubleSpinBox_mu->setValue(0.35);
        textEdit_Contraste_ImgPlusVual = new QTextEdit(centralWidget);
        textEdit_Contraste_ImgPlusVual->setObjectName(QStringLiteral("textEdit_Contraste_ImgPlusVual"));
        textEdit_Contraste_ImgPlusVual->setGeometry(QRect(950, 280, 104, 31));
        label_23 = new QLabel(centralWidget);
        label_23->setObjectName(QStringLiteral("label_23"));
        label_23->setGeometry(QRect(830, 290, 111, 16));
        label_24 = new QLabel(centralWidget);
        label_24->setObjectName(QStringLiteral("label_24"));
        label_24->setGeometry(QRect(820, 330, 131, 16));
        textEdit_Contraste_Restored = new QTextEdit(centralWidget);
        textEdit_Contraste_Restored->setObjectName(QStringLiteral("textEdit_Contraste_Restored"));
        textEdit_Contraste_Restored->setGeometry(QRect(950, 320, 104, 31));
        pushButton_IncreaseBrightness = new QPushButton(centralWidget);
        pushButton_IncreaseBrightness->setObjectName(QStringLiteral("pushButton_IncreaseBrightness"));
        pushButton_IncreaseBrightness->setGeometry(QRect(650, 360, 121, 23));
        doubleSpinBox_k = new QDoubleSpinBox(centralWidget);
        doubleSpinBox_k->setObjectName(QStringLiteral("doubleSpinBox_k"));
        doubleSpinBox_k->setGeometry(QRect(660, 320, 51, 22));
        doubleSpinBox_k->setMinimum(-99);
        doubleSpinBox_k->setSingleStep(0.5);
        doubleSpinBox_k->setValue(0.75);
        doubleSpinBox_b = new QDoubleSpinBox(centralWidget);
        doubleSpinBox_b->setObjectName(QStringLiteral("doubleSpinBox_b"));
        doubleSpinBox_b->setGeometry(QRect(740, 320, 62, 22));
        doubleSpinBox_b->setMinimum(-1000);
        doubleSpinBox_b->setMaximum(1000);
        doubleSpinBox_b->setSingleStep(10);
        doubleSpinBox_b->setValue(20);
        label_25 = new QLabel(centralWidget);
        label_25->setObjectName(QStringLiteral("label_25"));
        label_25->setGeometry(QRect(630, 320, 21, 16));
        label_26 = new QLabel(centralWidget);
        label_26->setObjectName(QStringLiteral("label_26"));
        label_26->setGeometry(QRect(720, 320, 21, 16));
        label_27 = new QLabel(centralWidget);
        label_27->setObjectName(QStringLiteral("label_27"));
        label_27->setGeometry(QRect(840, 250, 111, 16));
        textEdit_Contraste_Orig = new QTextEdit(centralWidget);
        textEdit_Contraste_Orig->setObjectName(QStringLiteral("textEdit_Contraste_Orig"));
        textEdit_Contraste_Orig->setGeometry(QRect(950, 240, 104, 31));
        textEdit_Difference_Contraste = new QTextEdit(centralWidget);
        textEdit_Difference_Contraste->setObjectName(QStringLiteral("textEdit_Difference_Contraste"));
        textEdit_Difference_Contraste->setGeometry(QRect(950, 370, 104, 31));
        label_28 = new QLabel(centralWidget);
        label_28->setObjectName(QStringLiteral("label_28"));
        label_28->setGeometry(QRect(820, 380, 121, 16));
        widget = new QCustomPlot(centralWidget);
        widget->setObjectName(QStringLiteral("widget"));
        widget->setGeometry(QRect(670, 420, 601, 271));
        pushButton_analise = new QPushButton(centralWidget);
        pushButton_analise->setObjectName(QStringLiteral("pushButton_analise"));
        pushButton_analise->setGeometry(QRect(1104, 370, 91, 23));
        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 1302, 21));
        MainWindow->setMenuBar(menuBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        MainWindow->setStatusBar(statusBar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", 0));
        label_Img1->setText(QString());
        pushButton_Gen_Image->setText(QApplication::translate("MainWindow", "GenImage", 0));
        label_3->setText(QApplication::translate("MainWindow", "X01:", 0));
        label_2->setText(QApplication::translate("MainWindow", "A1:", 0));
        label_5->setText(QApplication::translate("MainWindow", "SigmaX1:", 0));
        label_8->setText(QApplication::translate("MainWindow", "SigmaX2:", 0));
        label_13->setText(QApplication::translate("MainWindow", "SigmaX3:", 0));
        label_7->setText(QApplication::translate("MainWindow", "X02:", 0));
        label_12->setText(QApplication::translate("MainWindow", "X03:", 0));
        label_6->setText(QApplication::translate("MainWindow", "SigmaY1:", 0));
        label_11->setText(QApplication::translate("MainWindow", "Y02:", 0));
        label_16->setText(QApplication::translate("MainWindow", "Y03:", 0));
        label_9->setText(QApplication::translate("MainWindow", "SigmaY2:", 0));
        label_14->setText(QApplication::translate("MainWindow", "SigmaY3:", 0));
        label_10->setText(QApplication::translate("MainWindow", "A2:", 0));
        label_15->setText(QApplication::translate("MainWindow", "A3:", 0));
        label_4->setText(QApplication::translate("MainWindow", "Y01:", 0));
        label_Img2->setText(QString());
        label->setText(QApplication::translate("MainWindow", "alpha:", 0));
        label_Vual->setText(QString());
        label_18->setText(QApplication::translate("MainWindow", "Eps(ImgOrig, Img+Vual):", 0));
        label_19->setText(QApplication::translate("MainWindow", "Eps(ImgOrig, Img Filtered):", 0));
        pushButton_MedFilter_2->setText(QApplication::translate("MainWindow", "Median Filter NxN", 0));
        label_20->setText(QApplication::translate("MainWindow", "Wnd size:", 0));
        pushButton_LinFilter_2->setText(QApplication::translate("MainWindow", "Linear Filter NxN", 0));
        pushButton_LinFilter_3->setText(QApplication::translate("MainWindow", "Linear Gauss Filter NxN", 0));
        label_ImgMinus->setText(QString());
        pushButton->setText(QApplication::translate("MainWindow", "Result", 0));
        label_22->setText(QApplication::translate("MainWindow", "mu:", 0));
        label_23->setText(QApplication::translate("MainWindow", "Contraste (Img+Vual):", 0));
        label_24->setText(QApplication::translate("MainWindow", "Contraste (ImgRestored):", 0));
        pushButton_IncreaseBrightness->setText(QApplication::translate("MainWindow", "IncreaseBrightness", 0));
        label_25->setText(QApplication::translate("MainWindow", "k:", 0));
        label_26->setText(QApplication::translate("MainWindow", "b:", 0));
        label_27->setText(QApplication::translate("MainWindow", "Contraste (ImgOrigl):", 0));
        label_28->setText(QApplication::translate("MainWindow", "Ctr_Orig - Ctr_Restored:", 0));
        pushButton_analise->setText(QApplication::translate("MainWindow", "Analise", 0));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H

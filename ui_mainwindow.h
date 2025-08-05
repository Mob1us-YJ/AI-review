/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.15.15
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGraphicsView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QScrollArea>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralWidget;
    QLabel *label;
    QScrollArea *scrollArea;
    QWidget *scrollAreaWidgetContents_2;
    QWidget *verticalLayoutWidget;
    QVBoxLayout *verticalLayout;
    QLabel *label_num;
    QLabel *label_class_5;
    QLabel *label_discipline;
    QLabel *label_time;
    QLabel *label_quantity;
    QLabel *label_paper;
    QLabel *label_time_4;
    QLabel *label_state;
    QLabel *label_class;
    QLabel *label_time_6;
    QGraphicsView *graphicsView;
    QLabel *label_3;
    QLabel *label_4;
    QPushButton *pushButton;
    QPushButton *pushButton_2;
    QScrollArea *scrollArea_2;
    QWidget *scrollAreaWidgetContents_3;
    QWidget *verticalLayoutWidget_2;
    QVBoxLayout *verticalLayout_2;
    QWidget *verticalLayoutWidget_3;
    QVBoxLayout *verticalLayout_4;
    QWidget *verticalLayoutWidget_4;
    QVBoxLayout *verticalLayout_5;
    QWidget *verticalLayoutWidget_5;
    QVBoxLayout *verticalLayout_6;
    QWidget *verticalLayoutWidget_6;
    QVBoxLayout *verticalLayout_7;
    QWidget *verticalLayoutWidget_7;
    QVBoxLayout *verticalLayout_8;
    QLabel *label_class_3;
    QLabel *label_discipline_3;
    QLabel *label_quantity_3;
    QLabel *label_num_2;
    QLabel *label_time_3;
    QLabel *label_paper_3;
    QLabel *label_state_3;
    QLabel *label_class_4;
    QLabel *label_time_5;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(1280, 800);
        MainWindow->setAcceptDrops(false);
        MainWindow->setToolTipDuration(2);
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        label = new QLabel(centralWidget);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(30, 10, 181, 31));
        QFont font;
        font.setFamily(QString::fromUtf8("Agency FB"));
        font.setPointSize(18);
        font.setBold(false);
        font.setItalic(false);
        font.setWeight(50);
        label->setFont(font);
        label->setStyleSheet(QString::fromUtf8("color: rgb(255, 0, 0);\n"
"font: pt \"\345\276\256\350\275\257\351\233\205\351\273\221\";\n"
"font: 18pt \"Agency FB\";"));
        scrollArea = new QScrollArea(centralWidget);
        scrollArea->setObjectName(QString::fromUtf8("scrollArea"));
        scrollArea->setGeometry(QRect(10, 100, 1251, 101));
        scrollArea->setAutoFillBackground(true);
        scrollArea->setWidgetResizable(true);
        scrollAreaWidgetContents_2 = new QWidget();
        scrollAreaWidgetContents_2->setObjectName(QString::fromUtf8("scrollAreaWidgetContents_2"));
        scrollAreaWidgetContents_2->setGeometry(QRect(0, 0, 1249, 99));
        verticalLayoutWidget = new QWidget(scrollAreaWidgetContents_2);
        verticalLayoutWidget->setObjectName(QString::fromUtf8("verticalLayoutWidget"));
        verticalLayoutWidget->setGeometry(QRect(20, 40, 1211, 51));
        verticalLayout = new QVBoxLayout(verticalLayoutWidget);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        label_num = new QLabel(scrollAreaWidgetContents_2);
        label_num->setObjectName(QString::fromUtf8("label_num"));
        label_num->setGeometry(QRect(30, 0, 50, 41));
        QFont font1;
        font1.setFamily(QString::fromUtf8("Arial"));
        font1.setPointSize(16);
        font1.setBold(false);
        font1.setWeight(50);
        label_num->setFont(font1);
        label_class_5 = new QLabel(scrollAreaWidgetContents_2);
        label_class_5->setObjectName(QString::fromUtf8("label_class_5"));
        label_class_5->setGeometry(QRect(190, 0, 119, 39));
        QFont font2;
        font2.setFamily(QString::fromUtf8("Arial"));
        font2.setPointSize(14);
        font2.setBold(true);
        font2.setWeight(75);
        label_class_5->setFont(font2);
        label_discipline = new QLabel(scrollAreaWidgetContents_2);
        label_discipline->setObjectName(QString::fromUtf8("label_discipline"));
        label_discipline->setGeometry(QRect(501, 0, 115, 39));
        label_discipline->setFont(font2);
        label_time = new QLabel(scrollAreaWidgetContents_2);
        label_time->setObjectName(QString::fromUtf8("label_time"));
        label_time->setGeometry(QRect(983, 0, 116, 39));
        label_time->setFont(font2);
        label_quantity = new QLabel(scrollAreaWidgetContents_2);
        label_quantity->setObjectName(QString::fromUtf8("label_quantity"));
        label_quantity->setGeometry(QRect(863, 0, 115, 39));
        label_quantity->setFont(font2);
        label_paper = new QLabel(scrollAreaWidgetContents_2);
        label_paper->setObjectName(QString::fromUtf8("label_paper"));
        label_paper->setGeometry(QRect(621, 0, 116, 39));
        label_paper->setFont(font2);
        label_time_4 = new QLabel(scrollAreaWidgetContents_2);
        label_time_4->setObjectName(QString::fromUtf8("label_time_4"));
        label_time_4->setGeometry(QRect(1529, -1, 61, 39));
        label_time_4->setFont(font2);
        label_state = new QLabel(scrollAreaWidgetContents_2);
        label_state->setObjectName(QString::fromUtf8("label_state"));
        label_state->setGeometry(QRect(742, 0, 116, 39));
        label_state->setFont(font2);
        label_class = new QLabel(scrollAreaWidgetContents_2);
        label_class->setObjectName(QString::fromUtf8("label_class"));
        label_class->setGeometry(QRect(380, 0, 116, 39));
        label_class->setFont(font2);
        label_time_6 = new QLabel(scrollAreaWidgetContents_2);
        label_time_6->setObjectName(QString::fromUtf8("label_time_6"));
        label_time_6->setGeometry(QRect(1150, 0, 61, 39));
        label_time_6->setFont(font2);
        scrollArea->setWidget(scrollAreaWidgetContents_2);
        graphicsView = new QGraphicsView(centralWidget);
        graphicsView->setObjectName(QString::fromUtf8("graphicsView"));
        graphicsView->setGeometry(QRect(10, 0, 221, 51));
        label_3 = new QLabel(centralWidget);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setGeometry(QRect(560, 70, 201, 31));
        QFont font3;
        font3.setFamily(QString::fromUtf8("Arial"));
        font3.setPointSize(16);
        font3.setBold(true);
        font3.setWeight(75);
        label_3->setFont(font3);
        label_3->setAutoFillBackground(false);
        label_3->setStyleSheet(QString::fromUtf8("color: rgb(0, 0, 255);"));
        label_4 = new QLabel(centralWidget);
        label_4->setObjectName(QString::fromUtf8("label_4"));
        label_4->setGeometry(QRect(560, 240, 261, 31));
        label_4->setFont(font3);
        label_4->setStyleSheet(QString::fromUtf8("color: rgb(0, 0, 255);"));
        pushButton = new QPushButton(centralWidget);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));
        pushButton->setGeometry(QRect(20, 710, 531, 31));
        QFont font4;
        font4.setFamily(QString::fromUtf8("Agency FB"));
        font4.setPointSize(12);
        font4.setBold(true);
        font4.setWeight(75);
        pushButton->setFont(font4);
        pushButton_2 = new QPushButton(centralWidget);
        pushButton_2->setObjectName(QString::fromUtf8("pushButton_2"));
        pushButton_2->setGeometry(QRect(660, 710, 531, 31));
        pushButton_2->setFont(font4);
        scrollArea_2 = new QScrollArea(centralWidget);
        scrollArea_2->setObjectName(QString::fromUtf8("scrollArea_2"));
        scrollArea_2->setGeometry(QRect(10, 270, 1251, 411));
        scrollArea_2->setAutoFillBackground(true);
        scrollArea_2->setWidgetResizable(true);
        scrollAreaWidgetContents_3 = new QWidget();
        scrollAreaWidgetContents_3->setObjectName(QString::fromUtf8("scrollAreaWidgetContents_3"));
        scrollAreaWidgetContents_3->setGeometry(QRect(0, 0, 1249, 409));
        verticalLayoutWidget_2 = new QWidget(scrollAreaWidgetContents_3);
        verticalLayoutWidget_2->setObjectName(QString::fromUtf8("verticalLayoutWidget_2"));
        verticalLayoutWidget_2->setGeometry(QRect(20, 60, 1211, 51));
        verticalLayout_2 = new QVBoxLayout(verticalLayoutWidget_2);
        verticalLayout_2->setSpacing(6);
        verticalLayout_2->setContentsMargins(11, 11, 11, 11);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        verticalLayout_2->setContentsMargins(0, 0, 0, 0);
        verticalLayoutWidget_3 = new QWidget(scrollAreaWidgetContents_3);
        verticalLayoutWidget_3->setObjectName(QString::fromUtf8("verticalLayoutWidget_3"));
        verticalLayoutWidget_3->setGeometry(QRect(20, 120, 1211, 51));
        verticalLayout_4 = new QVBoxLayout(verticalLayoutWidget_3);
        verticalLayout_4->setSpacing(6);
        verticalLayout_4->setContentsMargins(11, 11, 11, 11);
        verticalLayout_4->setObjectName(QString::fromUtf8("verticalLayout_4"));
        verticalLayout_4->setContentsMargins(0, 0, 0, 0);
        verticalLayoutWidget_4 = new QWidget(scrollAreaWidgetContents_3);
        verticalLayoutWidget_4->setObjectName(QString::fromUtf8("verticalLayoutWidget_4"));
        verticalLayoutWidget_4->setGeometry(QRect(20, 180, 1211, 51));
        verticalLayout_5 = new QVBoxLayout(verticalLayoutWidget_4);
        verticalLayout_5->setSpacing(6);
        verticalLayout_5->setContentsMargins(11, 11, 11, 11);
        verticalLayout_5->setObjectName(QString::fromUtf8("verticalLayout_5"));
        verticalLayout_5->setContentsMargins(0, 0, 0, 0);
        verticalLayoutWidget_5 = new QWidget(scrollAreaWidgetContents_3);
        verticalLayoutWidget_5->setObjectName(QString::fromUtf8("verticalLayoutWidget_5"));
        verticalLayoutWidget_5->setGeometry(QRect(20, 240, 1211, 51));
        verticalLayout_6 = new QVBoxLayout(verticalLayoutWidget_5);
        verticalLayout_6->setSpacing(6);
        verticalLayout_6->setContentsMargins(11, 11, 11, 11);
        verticalLayout_6->setObjectName(QString::fromUtf8("verticalLayout_6"));
        verticalLayout_6->setContentsMargins(0, 0, 0, 0);
        verticalLayoutWidget_6 = new QWidget(scrollAreaWidgetContents_3);
        verticalLayoutWidget_6->setObjectName(QString::fromUtf8("verticalLayoutWidget_6"));
        verticalLayoutWidget_6->setGeometry(QRect(20, 300, 1211, 51));
        verticalLayout_7 = new QVBoxLayout(verticalLayoutWidget_6);
        verticalLayout_7->setSpacing(6);
        verticalLayout_7->setContentsMargins(11, 11, 11, 11);
        verticalLayout_7->setObjectName(QString::fromUtf8("verticalLayout_7"));
        verticalLayout_7->setContentsMargins(0, 0, 0, 0);
        verticalLayoutWidget_7 = new QWidget(scrollAreaWidgetContents_3);
        verticalLayoutWidget_7->setObjectName(QString::fromUtf8("verticalLayoutWidget_7"));
        verticalLayoutWidget_7->setGeometry(QRect(20, 360, 1211, 51));
        verticalLayout_8 = new QVBoxLayout(verticalLayoutWidget_7);
        verticalLayout_8->setSpacing(6);
        verticalLayout_8->setContentsMargins(11, 11, 11, 11);
        verticalLayout_8->setObjectName(QString::fromUtf8("verticalLayout_8"));
        verticalLayout_8->setContentsMargins(0, 0, 0, 0);
        label_class_3 = new QLabel(scrollAreaWidgetContents_3);
        label_class_3->setObjectName(QString::fromUtf8("label_class_3"));
        label_class_3->setGeometry(QRect(380, 10, 119, 39));
        label_class_3->setFont(font2);
        label_discipline_3 = new QLabel(scrollAreaWidgetContents_3);
        label_discipline_3->setObjectName(QString::fromUtf8("label_discipline_3"));
        label_discipline_3->setGeometry(QRect(504, 10, 119, 39));
        label_discipline_3->setFont(font2);
        label_quantity_3 = new QLabel(scrollAreaWidgetContents_3);
        label_quantity_3->setObjectName(QString::fromUtf8("label_quantity_3"));
        label_quantity_3->setGeometry(QRect(870, 10, 101, 39));
        label_quantity_3->setFont(font2);
        label_num_2 = new QLabel(scrollAreaWidgetContents_3);
        label_num_2->setObjectName(QString::fromUtf8("label_num_2"));
        label_num_2->setGeometry(QRect(30, 10, 50, 41));
        label_num_2->setFont(font1);
        label_time_3 = new QLabel(scrollAreaWidgetContents_3);
        label_time_3->setObjectName(QString::fromUtf8("label_time_3"));
        label_time_3->setGeometry(QRect(990, 10, 119, 39));
        label_time_3->setFont(font2);
        label_paper_3 = new QLabel(scrollAreaWidgetContents_3);
        label_paper_3->setObjectName(QString::fromUtf8("label_paper_3"));
        label_paper_3->setGeometry(QRect(628, 10, 119, 39));
        label_paper_3->setFont(font2);
        label_state_3 = new QLabel(scrollAreaWidgetContents_3);
        label_state_3->setObjectName(QString::fromUtf8("label_state_3"));
        label_state_3->setGeometry(QRect(750, 10, 101, 39));
        label_state_3->setFont(font2);
        label_class_4 = new QLabel(scrollAreaWidgetContents_3);
        label_class_4->setObjectName(QString::fromUtf8("label_class_4"));
        label_class_4->setGeometry(QRect(190, 10, 119, 39));
        label_class_4->setFont(font2);
        label_time_5 = new QLabel(scrollAreaWidgetContents_3);
        label_time_5->setObjectName(QString::fromUtf8("label_time_5"));
        label_time_5->setGeometry(QRect(1150, 10, 61, 39));
        label_time_5->setFont(font2);
        scrollArea_2->setWidget(scrollAreaWidgetContents_3);
        MainWindow->setCentralWidget(centralWidget);
        graphicsView->raise();
        label->raise();
        scrollArea->raise();
        label_3->raise();
        label_4->raise();
        pushButton->raise();
        pushButton_2->raise();
        scrollArea_2->raise();
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 1280, 19));
        MainWindow->setMenuBar(menuBar);
        mainToolBar = new QToolBar(MainWindow);
        mainToolBar->setObjectName(QString::fromUtf8("mainToolBar"));
        MainWindow->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        MainWindow->setStatusBar(statusBar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        label->setText(QCoreApplication::translate("MainWindow", "AI \351\230\205\345\215\267\347\263\273\347\273\237", nullptr));
        label_num->setText(QCoreApplication::translate("MainWindow", "\345\272\217\345\217\267", nullptr));
        label_class_5->setText(QCoreApplication::translate("MainWindow", "\350\200\203\350\257\225", nullptr));
        label_discipline->setText(QCoreApplication::translate("MainWindow", "\345\255\246\347\247\221", nullptr));
        label_time->setText(QCoreApplication::translate("MainWindow", "\346\227\245\346\234\237", nullptr));
        label_quantity->setText(QCoreApplication::translate("MainWindow", "\346\225\260\351\207\217", nullptr));
        label_paper->setText(QCoreApplication::translate("MainWindow", "\347\272\270\345\274\240", nullptr));
        label_time_4->setText(QCoreApplication::translate("MainWindow", "\346\223\215\344\275\234", nullptr));
        label_state->setText(QCoreApplication::translate("MainWindow", "\347\212\266\346\200\201", nullptr));
        label_class->setText(QCoreApplication::translate("MainWindow", "\347\217\255\347\272\247", nullptr));
        label_time_6->setText(QCoreApplication::translate("MainWindow", "\346\223\215\344\275\234", nullptr));
        label_3->setText(QCoreApplication::translate("MainWindow", "\346\211\253\346\217\217\344\273\273\345\212\241\345\210\227\350\241\250", nullptr));
        label_4->setText(QCoreApplication::translate("MainWindow", "\346\211\223\345\215\260\344\273\273\345\212\241\345\210\227\350\241\250", nullptr));
        pushButton->setText(QCoreApplication::translate("MainWindow", "\345\205\250\351\200\211", nullptr));
        pushButton_2->setText(QCoreApplication::translate("MainWindow", "\345\210\240\351\231\244", nullptr));
        label_class_3->setText(QCoreApplication::translate("MainWindow", "\347\217\255\347\272\247", nullptr));
        label_discipline_3->setText(QCoreApplication::translate("MainWindow", "\345\255\246\347\247\221", nullptr));
        label_quantity_3->setText(QCoreApplication::translate("MainWindow", "\346\225\260\351\207\217", nullptr));
        label_num_2->setText(QCoreApplication::translate("MainWindow", "\345\272\217\345\217\267", nullptr));
        label_time_3->setText(QCoreApplication::translate("MainWindow", "\346\227\245\346\234\237", nullptr));
        label_paper_3->setText(QCoreApplication::translate("MainWindow", "\347\272\270\345\274\240", nullptr));
        label_state_3->setText(QCoreApplication::translate("MainWindow", "\347\212\266\346\200\201", nullptr));
        label_class_4->setText(QCoreApplication::translate("MainWindow", "\350\200\203\350\257\225", nullptr));
        label_time_5->setText(QCoreApplication::translate("MainWindow", "\346\223\215\344\275\234", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H

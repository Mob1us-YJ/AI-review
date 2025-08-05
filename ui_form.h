/********************************************************************************
** Form generated from reading UI file 'form.ui'
**
** Created by: Qt User Interface Compiler version 5.15.15
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_FORM_H
#define UI_FORM_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Form
{
public:
    QPushButton *pushButton;
    QComboBox *comboBox;
    QLabel *label_num;
    QLabel *label_paper;
    QLabel *label_discipline;
    QLabel *label_class;
    QLabel *label_time;
    QLabel *label_state;
    QLabel *label_quantity;

    void setupUi(QWidget *Form)
    {
        if (Form->objectName().isEmpty())
            Form->setObjectName(QString::fromUtf8("Form"));
        Form->resize(1197, 53);
        Form->setAutoFillBackground(false);
        pushButton = new QPushButton(Form);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));
        pushButton->setGeometry(QRect(1110, 13, 80, 31));
        QFont font;
        font.setFamily(QString::fromUtf8("Agency FB"));
        font.setPointSize(12);
        font.setBold(true);
        font.setWeight(75);
        pushButton->setFont(font);
        comboBox = new QComboBox(Form);
        comboBox->addItem(QString());
        comboBox->addItem(QString());
        comboBox->addItem(QString());
        comboBox->addItem(QString());
        comboBox->setObjectName(QString::fromUtf8("comboBox"));
        comboBox->setGeometry(QRect(60, 13, 261, 31));
        QFont font1;
        font1.setFamily(QString::fromUtf8("Arial"));
        font1.setPointSize(10);
        font1.setBold(false);
        font1.setWeight(50);
        comboBox->setFont(font1);
        label_num = new QLabel(Form);
        label_num->setObjectName(QString::fromUtf8("label_num"));
        label_num->setGeometry(QRect(20, 10, 50, 31));
        QFont font2;
        font2.setFamily(QString::fromUtf8("Arial"));
        font2.setPointSize(12);
        font2.setBold(false);
        font2.setWeight(50);
        label_num->setFont(font2);
        label_paper = new QLabel(Form);
        label_paper->setObjectName(QString::fromUtf8("label_paper"));
        label_paper->setGeometry(QRect(598, 10, 121, 39));
        label_paper->setFont(font2);
        label_discipline = new QLabel(Form);
        label_discipline->setObjectName(QString::fromUtf8("label_discipline"));
        label_discipline->setGeometry(QRect(490, 10, 81, 39));
        label_discipline->setFont(font2);
        label_class = new QLabel(Form);
        label_class->setObjectName(QString::fromUtf8("label_class"));
        label_class->setGeometry(QRect(340, 10, 131, 39));
        label_class->setFont(font2);
        label_time = new QLabel(Form);
        label_time->setObjectName(QString::fromUtf8("label_time"));
        label_time->setGeometry(QRect(920, 10, 141, 39));
        label_time->setFont(font2);
        label_state = new QLabel(Form);
        label_state->setObjectName(QString::fromUtf8("label_state"));
        label_state->setGeometry(QRect(724, 10, 91, 39));
        label_state->setFont(font2);
        label_quantity = new QLabel(Form);
        label_quantity->setObjectName(QString::fromUtf8("label_quantity"));
        label_quantity->setGeometry(QRect(860, 10, 81, 39));
        label_quantity->setFont(font2);
        QWidget::setTabOrder(pushButton, comboBox);

        retranslateUi(Form);

        QMetaObject::connectSlotsByName(Form);
    } // setupUi

    void retranslateUi(QWidget *Form)
    {
        Form->setWindowTitle(QCoreApplication::translate("Form", "Form", nullptr));
        pushButton->setText(QCoreApplication::translate("Form", "\346\211\253\346\217\217", nullptr));
        comboBox->setItemText(0, QCoreApplication::translate("Form", "2025\345\271\264\344\270\212\347\254\254\344\270\200\346\254\241\346\234\210\350\200\203", nullptr));
        comboBox->setItemText(1, QCoreApplication::translate("Form", "2025\345\271\264\344\270\212\347\254\254\344\272\214\346\254\241\346\234\210\350\200\203", nullptr));
        comboBox->setItemText(2, QCoreApplication::translate("Form", "2025\345\271\264\344\270\213\347\254\254\344\270\200\346\254\241\346\234\210\350\200\203", nullptr));
        comboBox->setItemText(3, QCoreApplication::translate("Form", "2025\345\271\264\344\270\213\347\254\254\344\270\200\346\254\241\346\234\210\350\200\203", nullptr));

        label_num->setText(QCoreApplication::translate("Form", "NO", nullptr));
        label_paper->setText(QCoreApplication::translate("Form", "A3\345\217\214\351\235\242", nullptr));
        label_discipline->setText(QCoreApplication::translate("Form", "\346\225\260\345\255\246", nullptr));
        label_class->setText(QCoreApplication::translate("Form", "\351\253\230\344\270\200\357\274\21013\357\274\211", nullptr));
        label_time->setText(QCoreApplication::translate("Form", "20250804", nullptr));
        label_state->setText(QCoreApplication::translate("Form", "\345\276\205\346\211\253\346\217\217", nullptr));
        label_quantity->setText(QCoreApplication::translate("Form", "50", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Form: public Ui_Form {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_FORM_H

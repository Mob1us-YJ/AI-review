#include "form.h"
#include "ui_form.h"
#include <QDebug>

Form::Form(QString pnum, QString pclass, QString pdiscipline, QString ppaper, QString pstate, QString pquantity, QString ptime, QString pbutton, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Form),
    m_taskId(pnum),
    m_className(pclass),
    m_subject(pdiscipline),
    m_buttonType(pbutton)
{
    ui->setupUi(this);
    this->setFixedHeight(55);                         //设置界面
    this->setObjectName("form");
    this->setAttribute(Qt::WA_StyledBackground,true); //子界面需要加这个才能修改背景

    //hover表示鼠标移动到form界面时的样式
    this->setStyleSheet("QWidget#form{background-color:rgb(255,255,255)}"
                            "QWidget#form:hover{background-color:rgb(203,203,203)}QLabel{color:rgb(0,0,0);}");


    ui->label_num->setText(pnum);
    ui->label_class->setText(pclass);
    ui->label_discipline->setText(pdiscipline);
    ui->label_paper->setText(ppaper);
    ui->label_state->setText(pstate);
    ui->label_quantity->setText(pquantity);
    ui->label_time->setText(ptime);
    ui->pushButton->setText(pbutton);
    
    // 连接按钮点击信号
    connect(ui->pushButton, &QPushButton::clicked, this, &Form::onPushButtonClicked);
}

Form::~Form()
{
    delete ui;
}

void Form::onPushButtonClicked()
{
    qDebug() << "Form按钮被点击:" << m_buttonType << "任务ID:" << m_taskId;
    
    if (m_buttonType == "扫描") {
        emit scanButtonClicked(m_taskId, m_className, m_subject);
    } else if (m_buttonType == "打印") {
        emit printButtonClicked(m_taskId, m_className, m_subject);
    }
}

#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
//    QPalette pal;
//    pal.setColor(QPalette::Window,QColor(Qt::white));
//    this->setPalette(pal);
    ui->setupUi(this);
    //先添加6个
       Form *form = new Form("1","高一（13）","数学","A3双面","待扫描","50","2025/8/2 8:07:25","扫描");
       ui->verticalLayout->addWidget(form);                //加入布局
       Form *form_1 = new Form("1","高一（12）","数学","A3双面","待扫描","50","2025/8/2 8:07:25","打印");
       ui->verticalLayout_2->addWidget(form_1);            //加入布局
       Form *form_2 = new Form("2","高一（12）","语文","A3双面","待扫描","50","2025/8/2 8:07:25","打印");
       ui->verticalLayout_4->addWidget(form_2);            //加入布局
       Form *form_3 = new Form("3","高一（12）","英语","A3双面","待扫描","50","2025/8/2 8:07:25","打印");
       ui->verticalLayout_5->addWidget(form_3);            //加入布局
       Form *form_4 = new Form("4","高一（12）","物理","A3双面","待扫描","50","2025/8/2 8:07:25","打印");
       ui->verticalLayout_6->addWidget(form_4);            //加入布局
       Form *form_5 = new Form("5","高一（12）","数学","A3双面","待扫描","50","2025/8/2 8:07:25","打印");
       ui->verticalLayout_7->addWidget(form_5);            //加入布局
       Form *form_6 = new Form("6","高一（12）","数学","A3双面","待扫描","50","2025/8/2 8:07:25","打印");
       ui->verticalLayout_8->addWidget(form_6);            //加入布局


}

MainWindow::~MainWindow()
{
    delete ui;
}

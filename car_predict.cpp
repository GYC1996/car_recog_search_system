#include <QtWidgets>
#include <iostream>
#include "car_label_predict.h"
#include "car_predict.h"
#include "ui_car_predict.h"
#include <QMainWindow>
using namespace std;

Car_Predict::Car_Predict(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Car_Predict)
{
    ui->setupUi(this);
    //this->resize( QSize( 1000, 500 ));
    openAction = new QAction(QIcon(":/image/file-open"), tr("&Open..."), this);
    openAction->setShortcuts(QKeySequence::Open);//定义快捷键
    openAction->setStatusTip(tr("Open an existing file"));
    //实现了当用户鼠标滑过这个 action 时，会在主窗口下方的状态栏显示相应的提示
    connect(openAction, &QAction::triggered, this, &Car_Predict::on_open_clicked);
    //将这个QAction的triggered()信号与Car_Predict类的open()函数连接起来。
    //当用户点击了这个QAction时，会自动触发Car_Predict的open()函数

    saveAction = new QAction(QIcon(":/image/predict"), tr("&Predict..."), this);
    saveAction->setShortcuts(QKeySequence::Save);
    saveAction->setStatusTip(tr("Save a new file"));
    connect(saveAction, &QAction::triggered, this, &Car_Predict::on_predict_clicked);

    //QMenu *file = ui -> menuBar -> addMenu(tr("&File"));
    QMenu *file = ui ->menubar-> addMenu(tr("&File"));
    file->addAction(openAction);
    file->addAction(saveAction);

    //QToolBar *toolBar =  mainToolBar(tr("&File"));//工具栏
    //QToolBar *toolBar = addToolBar(tr("&Filelililili"));
    //QToolBar *toolBar = ui->mainToolBar;
    QToolBar *toolBar = ui->toolBar;
    toolBar->addAction(openAction);
    toolBar->addAction(saveAction);

    path= "/home/guoyuechao/图片/background.png";
    QImage image = QImageReader ( path ).read();
    QImage result = image.scaled(800, 600).scaled(381,//放缩图片，以固定大小显示
                                                  431, Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
    ui->show_pic->setPixmap(QPixmap::fromImage(result));
    ui->show_pic->show();
}

Car_Predict::~Car_Predict()
{
    delete ui;
}

void Car_Predict::receive_from_login()
{
    this->show();
}

void Car_Predict::on_open_clicked()
{
    path = QFileDialog::getOpenFileName(this, tr("Select an image"), ".",
                                                tr("Text Files(*.jpg *.png)"));
    //cout<<path.toStdString()<<"vcv"<<endl;
   // QUrl Uri ( QString ( "file://%1" ).arg ( path ) );
    QImage image = QImageReader ( path ).read();
    //QImage result = image.scaled(1000, 1000).scaled(500, 500, Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
    QImage result = image.scaled(762, 862).scaled(381,//放缩图片，以固定大小显示
                                                  431, Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
    ui->show_pic->setPixmap(QPixmap::fromImage(result));
    ui->show_pic->show();
}

void Car_Predict::on_predict_clicked()
{
    std::string cstr=string((const char *)path.toLocal8Bit());
    Mat img = imread(cstr);

    cout<<"structing start"<<endl;
    CarPredict net;
    cout<<"structing end"<<endl;
    net.predict(img);
    cout<<"predict end"<<endl;

    std::cout << "Best class type: #" << net.getId() << " '" << net.getName() << "'" << std::endl;
    std::cout << "Best class color: #" << net.getId2() << " '" << net.getName2() << "'" << std::endl;
    std::cout << "Probability: " << net.getProb() * 100 << "%" << std::endl;
    std::cout << "Probability: " << net.getProb2() * 100 << "%" << std::endl;
    std::cout << "Costtime: " << net.getTime() << "ms" << std::endl;
    QString name=QString::fromStdString(net.getName());
    QString name2=QString::fromStdString(net.getName2());
    ui->type->setText(name);
    ui->color->setText(name2);
}

void Car_Predict::on_pushButton_clicked()
{
    this->hide();
    emit showpic();
    path= "/home/guoyuechao/图片/background.png";
    QImage image = QImageReader ( path ).read();
    QImage result = image.scaled(800, 600).scaled(381,//放缩图片，以固定大小显示
                                                  431, Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
    ui->show_pic->setPixmap(QPixmap::fromImage(result));
    ui->show_pic->show();
    ui->color->setText("");
    ui->type->setText("");
}

void Car_Predict::on_pushButton_2_clicked()
{
    this->hide();
    emit exit();    
    path= "/home/guoyuechao/图片/background.png";
    QImage image = QImageReader ( path ).read();
    QImage result = image.scaled(800, 600).scaled(381,//放缩图片，以固定大小显示
                                                  431, Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
    ui->show_pic->setPixmap(QPixmap::fromImage(result));
    ui->show_pic->show();
    ui->color->setText("");
    ui->type->setText("");
}

void Car_Predict::rec_from_search()
{
    this->show();
}

#include "car_search.h"
#include "ui_car_search.h"
#include <QDebug>
#include <fstream>
#include <sstream>
#include <QImageReader>
#include <QMainWindow>
#include <QtWidgets>

car_search::car_search(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::car_search)
{
    ui->setupUi(this);
    QString whole_path="/home/guoyuechao/图片/bg3.png";
    QImage image = QImageReader ( whole_path ).read();
    QImage result = image.scaled(762, 862).scaled(361,//放缩图片，以固定大小显示
                                                      361, Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
    ui->show_pic->setPixmap(QPixmap::fromImage(result));
    ui->show_pic->show();
    ui->pushButton_2->setEnabled(false);
    ui->pushButton_3->setEnabled(false);
}

car_search::~car_search()
{
    delete ui;
}

void car_search::on_pushButton_clicked()
{
    ui->pushButton_2->setEnabled(false);
    ui->pushButton_3->setEnabled(false);
    path_part_lists.clear();
    QString car_color=ui->car_color->currentText();
    QString car_type=ui->car_type->currentText();
    int car_color_list=ui->car_color->currentIndex();
    int car_type_list=ui->car_type->currentIndex();
    qDebug()<<car_color<<" "<<car_type<<" "<<car_color_list<<" "<<car_type_list;

    ifstream fp("car_database.txt");
    if(!fp.is_open())
    {
        cout<<"打开失败";
    }
    string lines;
    string path_part;
    int color_index;
    int type_index;
    int find_first_,find_second_,find_third_;
    while(!fp.eof())
    {
        getline(fp,lines);
        find_first_=lines.find(" ");
        path_part=lines.substr(0,find_first_);
        lines=lines.substr(find_first_+1,lines.size()-find_first_-1);
        find_second_=lines.find(" ");
        stringstream stream(lines.substr(0,find_second_));
        stream>>type_index;
        lines=lines.substr(find_second_+1,lines.size()-find_second_-1);
        find_third_=lines.find("\n");
        stringstream stream2(lines.substr(0,find_third_));
        stream2>>color_index;
        //cout<<path_part<<" "<<color_index<<" "<<type_index<<endl;
        if(car_color_list==10 && car_type_list==12)
        {
            path_part_lists.push_back(path_part);
            cout<<path_part<<endl;
        }
        else if(car_color_list==10 && car_type_list!=12)
        {
            if(type_index==car_type_list)
            {
                path_part_lists.push_back(path_part);
                cout<<path_part<<endl;
            }
        }
        else if(car_color_list!=10 && car_type_list==12)
        {
            if(color_index==car_color_list)
            {
                path_part_lists.push_back(path_part);
                cout<<path_part<<endl;
            }
        }
        else
        {
            if((type_index==car_type_list) && (color_index==car_color_list))
            {
                path_part_lists.push_back(path_part);
                cout<<path_part<<endl;
            }
        }
    }
    fp.close();
    count=0;
    total=path_part_lists.size();
    if(total==0)
    {
        ui->show_pic->setText("库中没有对应图片");
    }
    else
    {
        QString whole_path="/home/guoyuechao/caffe-package/caffe/data/car281/image/"
                +QString::fromStdString(path_part_lists[count]);
        QImage image = QImageReader ( whole_path ).read();
        QImage result = image.scaled(762, 862).scaled(361,//放缩图片，以固定大小显示
                                                          361, Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
        ui->show_pic->setPixmap(QPixmap::fromImage(result));
        ui->show_pic->show();
        qDebug()<<whole_path<<count;
        ui->pushButton_2->setEnabled(true);
        cout<<endl<<endl<<endl;
    }
}

void car_search::receive_from_predict()
{
    this->show();
}

void car_search::on_pushButton_2_clicked()
{
    count++;
    if(count>=total-1)
    {
        ui->pushButton_2->setEnabled(false);
    }
    QString whole_path="/home/guoyuechao/caffe-package/caffe/data/car281/image/"
            +QString::fromStdString(path_part_lists[count]);
    QImage image = QImageReader ( whole_path ).read();
    QImage result = image.scaled(762, 862).scaled(361,//放缩图片，以固定大小显示
                                                      361, Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
    ui->show_pic->setPixmap(QPixmap::fromImage(result));
    ui->show_pic->show();
    qDebug()<<whole_path<<count;
    ui->pushButton_3->setEnabled(true);
//    count++;
}

void car_search::on_pushButton_3_clicked()
{
    count--;
    if(count<=0)
    {
        ui->pushButton_3->setEnabled(false);
        cout<<count;
    }
    QString whole_path="/home/guoyuechao/caffe-package/caffe/data/car281/image/"
            +QString::fromStdString(path_part_lists[count]);
    QImage image = QImageReader ( whole_path ).read();
    QImage result = image.scaled(762, 862).scaled(361,//放缩图片，以固定大小显示
                                                      361, Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
    ui->show_pic->setPixmap(QPixmap::fromImage(result));
    ui->show_pic->show();
    qDebug()<<whole_path<<count;
    ui->pushButton_2->setEnabled(true);
//    count--;
}


void car_search::on_pushButton_4_clicked()
{
    this->hide();
    emit back();
    QString whole_path="/home/guoyuechao/图片/bg3.png";
    QImage image = QImageReader ( whole_path ).read();
    QImage result = image.scaled(762, 862).scaled(361,//放缩图片，以固定大小显示
                                                      361, Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
    ui->show_pic->setPixmap(QPixmap::fromImage(result));
    ui->show_pic->show();
    ui->pushButton_2->setEnabled(false);
    ui->pushButton_3->setEnabled(false);
}

void car_search::on_pushButton_5_clicked()
{
    this->hide();
    emit exit();
    QString whole_path="/home/guoyuechao/图片/bg3.png";
    QImage image = QImageReader ( whole_path ).read();
    QImage result = image.scaled(762, 862).scaled(361,//放缩图片，以固定大小显示
                                                      361, Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
    ui->show_pic->setPixmap(QPixmap::fromImage(result));
    ui->show_pic->show();
    ui->pushButton_2->setEnabled(false);
    ui->pushButton_3->setEnabled(false);
}

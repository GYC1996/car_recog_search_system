#include "mainwindow.h"
#include "car_predict.h"
#include "car_search.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    Car_Predict u;
    car_search v;
    w.show();
    QObject::connect(&w,SIGNAL(showmain()),&u,SLOT(receive_from_login()));
    QObject::connect(&u,SIGNAL(showpic()),&v,SLOT(receive_from_predict()));
    QObject::connect(&u,SIGNAL(exit()),&w,SLOT(rece_exit_from_pre()));
    QObject::connect(&v,SIGNAL(back()),&u,SLOT(rec_from_search()));
    QObject::connect(&v,SIGNAL(exit()),&w,SLOT(recv_exit_from_search()));
    return a.exec();
}

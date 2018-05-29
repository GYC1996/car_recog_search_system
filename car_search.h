#ifndef CAR_SEARCH_H
#define CAR_SEARCH_H

#include <QMainWindow>
#include <vector>
#include <string>
#include <iostream>
#include <QDebug>
using namespace std;
namespace Ui {
class car_search;
}

class car_search : public QMainWindow
{
    Q_OBJECT

public:
    explicit car_search(QWidget *parent = 0);
    ~car_search();

signals:
    void back();
    void exit();

private slots:
    void on_pushButton_clicked();
    //void showPic();


    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

private slots:
    void receive_from_predict();//与dialog发送信号相关联的信号

    void on_pushButton_4_clicked();

    void on_pushButton_5_clicked();

private:
    Ui::car_search *ui;
    int count,total;
    vector<string>path_part_lists;
};

#endif // CAR_SEARCH_H

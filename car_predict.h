#ifndef CAR_PREDICT_H
#define CAR_PREDICT_H

#include <QMainWindow>

namespace Ui {
class Car_Predict;
}

class Car_Predict : public QMainWindow
{
    Q_OBJECT

public:
    explicit Car_Predict(QWidget *parent = 0);
    ~Car_Predict();

private slots:
    void receive_from_login();//与dialog发送信号相关联的信号
    void rec_from_search();

private slots:
    void on_open_clicked();

    void on_predict_clicked();

    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

private:
    QAction *openAction;
    QAction *saveAction;
    QString path;

signals:
    void showpic();
    void exit();

private:
    Ui::Car_Predict *ui;
};

#endif // CAR_PREDICT_H

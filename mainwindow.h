#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSqlDatabase>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    QSqlDatabase DatabaseConnect();
    bool CreatDataTable();
    ~MainWindow();

private slots://槽
    void on_pushButton_clicked();
    void rece_exit_from_pre();
    void recv_exit_from_search();
//增加一个信号，用于将此信号传送给其他页面，以实现页面跳转功能
    void on_pushButton_2_clicked();

signals:
    void showmain();//显示主界面
    //此函数不需要在CPP文件实现，因为它只作为信号进行传输到特定页面即可


private:
    Ui::MainWindow *ui;
    QSqlDatabase database;
};

#endif // MAINWINDOW_H

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QSqlError>
#include <QSqlQuery>
#include <QDebug>
#include <iostream>
#include <QMessageBox>
using namespace std;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{

    ui->setupUi(this);
    ui->password->setEchoMode(QLineEdit::Password);
    this->database=DatabaseConnect();
    CreatDataTable();

}

QSqlDatabase MainWindow::DatabaseConnect()
{
    QSqlDatabase database;
    if(QSqlDatabase::contains("qt_sql_default_connection"))
    {
        database=QSqlDatabase::database("qt_sql_default_connection");
        //qDebug()<<"a";
    }
    else
    {
        database=QSqlDatabase::addDatabase("QSQLITE","qt_sql_default_connection");
        database.setDatabaseName("MyDatabase.db");
        //qDebug()<<"b";
    }
    if(!database.open())
    {
        qDebug() << "Error: Failed to connect database." << database.lastError();
    }
    return database;
}

bool MainWindow::CreatDataTable()
{
    QSqlQuery sql_query(this->database);
    QStringList tables=this->database.tables();
    if(tables.contains("login"))
    {
        qDebug()<<"the table has exited";
    }
    else
    {
        QString creat_sql="create table login (username string primary key,password string)";
        sql_query.prepare(creat_sql);
        if(!sql_query.exec())
        {
             qDebug()<<"Fail to creat table"<<sql_query.lastError();
             return 0;
        }
        else
        {
            qDebug()<<"the table has created!";
            return 1;
        }
    }
}

void MainWindow::rece_exit_from_pre()
{
    this->show();
}

void MainWindow::recv_exit_from_search()
{
    this->show();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    QSqlQuery sql_query(this->database);
    QString usernames=ui->user_name->text();
    QString passwords=ui->password->text();
    qDebug()<<usernames<<" "<<endl;
    qDebug()<<passwords<<" "<<endl;
    if(usernames.size()<7)
    {
        QMessageBox::critical(this,tr("提示"),tr("用户名不得少于7位"),QMessageBox::Yes);
        ui->user_name->setText("");
        ui->password->setText("");
        return ;
    }
    if(passwords.size()<7)
    {
        QMessageBox::critical(this,tr("提示"),tr("密码不得少于7位"),QMessageBox::Yes);
        ui->user_name->setText("");
        ui->password->setText("");
        return ;
    }
    QString select_sql="select * from login where username=?";
    sql_query.prepare(select_sql);
    sql_query.addBindValue(usernames);
    if(sql_query.exec())
    {
        qDebug()<<"select success";
    }
    else
    {
        qDebug()<<"select failed"<<sql_query.lastError();

    }
    if(sql_query.first())
    {
        QString password=sql_query.value(1).toString();
        if(password==passwords)
        {
            qDebug()<<"Login success";
            this->hide();//屏蔽登陆界面
            emit showmain();  //激活信号，让信号传送到特定页面
            if(!ui->radioButton->isChecked())
                ui->password->setText("");
        }
        else
        {
            qDebug()<<"password is wrong";
            QMessageBox::critical(this,tr("提示"),tr("密码错误"),QMessageBox::Yes);
            ui->user_name->setText("");
            ui->password->setText("");
        }
    }
    else
    {
        qDebug()<<"the username is not exsit,please register first";
        QMessageBox::critical(this,tr("提示"),tr("用户名不存在"),QMessageBox::Yes);
    }
}

void MainWindow::on_pushButton_2_clicked()
{//注册
    QSqlQuery sql_query(this->database);
    QString insert_sql="insert into login values(?,?)";
    sql_query.prepare(insert_sql);
    QString usernames=ui->user_name->text();
    QString passwords=ui->password->text();
    sql_query.addBindValue(usernames);
    sql_query.addBindValue(passwords);
    if(!sql_query.exec())
    {
        qDebug()<<"register failed"<<sql_query.lastError();
        QMessageBox::critical(this,tr("提示"),tr("用户名已存在"),QMessageBox::Yes);
        ui->user_name->setText("");
        ui->password->setText("");
    }
    else
    {
        qDebug()<<"register success";
        //QMessageBox::warning(this,tr("提示"),tr("注册成功"),QMessageBox::Yes);
        QMessageBox::about(NULL, "提示", "注册成功");
        ui->password->setText("");
    }
}


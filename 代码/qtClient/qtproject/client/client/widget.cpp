#include "widget.h"
#include "ui_widget.h"
#include <QDebug>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);

    //this->setFixedSize(800,600);

    socket = new QTcpSocket();
    ui->conn_btn->setCheckable(true);   //设置checked为true表示未连接服务器
}

Widget::~Widget()
{
    delete ui;
}


void Widget::on_close_btn_clicked()
{
    if(socket->isOpen())
    {
        //关闭连接
        socket->disconnectFromHost();
        socket->close();
    }

    this->close();
}

void Widget::on_conn_btn_clicked(bool checked)
{
    if(checked)
    {
        socket->connectToHost(ui->ip_edit->text(), ui->port_edit->text().toUInt());     //连接服务器
        if(socket->isOpen())
        {
            qDebug() << "client connect server success!";
        }
        connect(socket, SIGNAL(connected()), this, SLOT(on_send_btn_clicked()));

        connect(socket, &QTcpSocket::readyRead, [=](){        //
           QByteArray data = socket->readAll();
           ui->recv_massage->setText(QString::fromUtf8(data));
        });

        checked = false;
    }
    else
    {
       socket->disconnectFromHost();
       socket->close();

       //断开槽函数
       disconnect(socket, SIGNAL(readyRead()), this, SLOT(on_recv_massage_linkActivated(QString)));

       qDebug() << "client han quit!";
       checked = true;
    }
}

void Widget::on_send_btn_clicked()
{
    if(nullptr == socket)
    {
        return;
    }
    QString buf = ui->massage_2->text();  //获取recv的信息

    socket->write(buf.toUtf8().data()); //向服务器发送数据

     qDebug() << "client send massage:" << buf.toUtf8().data();
}

void Widget::on_recv_massage_linkActivated(const QString &link)
{
    QByteArray data = socket->readAll();

    ui->recv_massage->setText(QString::fromUtf8(data));
}

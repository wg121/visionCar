#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QTcpSocket>

QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();

private slots:
    void on_close_btn_clicked();

    void on_conn_btn_clicked(bool checked);

    void on_send_btn_clicked();

    void on_recv_massage_linkActivated(const QString &link);

private:
    Ui::Widget *ui;

    QTcpSocket *socket;
};
#endif // WIDGET_H

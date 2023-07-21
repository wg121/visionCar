/********************************************************************************
** Form generated from reading UI file 'widget.ui'
**
** Created by: Qt User Interface Compiler version 5.9.9
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_WIDGET_H
#define UI_WIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Widget
{
public:
    QVBoxLayout *verticalLayout_4;
    QSpacerItem *verticalSpacer;
    QWidget *widget_6;
    QHBoxLayout *horizontalLayout_4;
    QSpacerItem *horizontalSpacer;
    QPushButton *conn_btn;
    QSpacerItem *horizontalSpacer_9;
    QWidget *widget_2;
    QVBoxLayout *verticalLayout;
    QLabel *port_lab;
    QLabel *ip_lab;
    QWidget *widget_3;
    QVBoxLayout *verticalLayout_2;
    QLineEdit *ip_edit;
    QLineEdit *port_edit;
    QSpacerItem *horizontalSpacer_2;
    QSpacerItem *verticalSpacer_5;
    QWidget *widget_4;
    QHBoxLayout *horizontalLayout_2;
    QPushButton *send_btn;
    QLineEdit *massage_2;
    QSpacerItem *verticalSpacer_4;
    QWidget *widget_5;
    QHBoxLayout *horizontalLayout_3;
    QLabel *recv_lab;
    QLabel *recv_massage;
    QSpacerItem *verticalSpacer_3;
    QWidget *widget;
    QHBoxLayout *horizontalLayout;
    QSpacerItem *horizontalSpacer_3;
    QPushButton *close_btn;
    QSpacerItem *horizontalSpacer_4;
    QSpacerItem *verticalSpacer_2;

    void setupUi(QWidget *Widget)
    {
        if (Widget->objectName().isEmpty())
            Widget->setObjectName(QStringLiteral("Widget"));
        Widget->resize(800, 600);
        verticalLayout_4 = new QVBoxLayout(Widget);
        verticalLayout_4->setObjectName(QStringLiteral("verticalLayout_4"));
        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_4->addItem(verticalSpacer);

        widget_6 = new QWidget(Widget);
        widget_6->setObjectName(QStringLiteral("widget_6"));
        horizontalLayout_4 = new QHBoxLayout(widget_6);
        horizontalLayout_4->setObjectName(QStringLiteral("horizontalLayout_4"));
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_4->addItem(horizontalSpacer);

        conn_btn = new QPushButton(widget_6);
        conn_btn->setObjectName(QStringLiteral("conn_btn"));
        QFont font;
        font.setPointSize(12);
        conn_btn->setFont(font);

        horizontalLayout_4->addWidget(conn_btn);

        horizontalSpacer_9 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_4->addItem(horizontalSpacer_9);

        widget_2 = new QWidget(widget_6);
        widget_2->setObjectName(QStringLiteral("widget_2"));
        verticalLayout = new QVBoxLayout(widget_2);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        port_lab = new QLabel(widget_2);
        port_lab->setObjectName(QStringLiteral("port_lab"));
        port_lab->setFont(font);

        verticalLayout->addWidget(port_lab);

        ip_lab = new QLabel(widget_2);
        ip_lab->setObjectName(QStringLiteral("ip_lab"));
        ip_lab->setFont(font);

        verticalLayout->addWidget(ip_lab);


        horizontalLayout_4->addWidget(widget_2);

        widget_3 = new QWidget(widget_6);
        widget_3->setObjectName(QStringLiteral("widget_3"));
        verticalLayout_2 = new QVBoxLayout(widget_3);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        ip_edit = new QLineEdit(widget_3);
        ip_edit->setObjectName(QStringLiteral("ip_edit"));

        verticalLayout_2->addWidget(ip_edit);

        port_edit = new QLineEdit(widget_3);
        port_edit->setObjectName(QStringLiteral("port_edit"));

        verticalLayout_2->addWidget(port_edit);


        horizontalLayout_4->addWidget(widget_3);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_4->addItem(horizontalSpacer_2);


        verticalLayout_4->addWidget(widget_6);

        verticalSpacer_5 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_4->addItem(verticalSpacer_5);

        widget_4 = new QWidget(Widget);
        widget_4->setObjectName(QStringLiteral("widget_4"));
        horizontalLayout_2 = new QHBoxLayout(widget_4);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        send_btn = new QPushButton(widget_4);
        send_btn->setObjectName(QStringLiteral("send_btn"));
        send_btn->setFont(font);

        horizontalLayout_2->addWidget(send_btn);

        massage_2 = new QLineEdit(widget_4);
        massage_2->setObjectName(QStringLiteral("massage_2"));

        horizontalLayout_2->addWidget(massage_2);


        verticalLayout_4->addWidget(widget_4);

        verticalSpacer_4 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_4->addItem(verticalSpacer_4);

        widget_5 = new QWidget(Widget);
        widget_5->setObjectName(QStringLiteral("widget_5"));
        horizontalLayout_3 = new QHBoxLayout(widget_5);
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        recv_lab = new QLabel(widget_5);
        recv_lab->setObjectName(QStringLiteral("recv_lab"));
        recv_lab->setEnabled(false);
        recv_lab->setMinimumSize(QSize(50, 30));
        recv_lab->setMaximumSize(QSize(80, 30));
        QFont font1;
        font1.setFamily(QStringLiteral("Arial Rounded MT Bold"));
        font1.setPointSize(12);
        font1.setBold(true);
        font1.setUnderline(false);
        font1.setWeight(75);
        recv_lab->setFont(font1);

        horizontalLayout_3->addWidget(recv_lab);

        recv_massage = new QLabel(widget_5);
        recv_massage->setObjectName(QStringLiteral("recv_massage"));
        recv_massage->setEnabled(true);
        recv_massage->setFont(font);
        recv_massage->setContextMenuPolicy(Qt::NoContextMenu);
        recv_massage->setFrameShape(QFrame::Box);
        recv_massage->setFrameShadow(QFrame::Sunken);

        horizontalLayout_3->addWidget(recv_massage);


        verticalLayout_4->addWidget(widget_5);

        verticalSpacer_3 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_4->addItem(verticalSpacer_3);

        widget = new QWidget(Widget);
        widget->setObjectName(QStringLiteral("widget"));
        widget->setMinimumSize(QSize(30, 30));
        horizontalLayout = new QHBoxLayout(widget);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_3);

        close_btn = new QPushButton(widget);
        close_btn->setObjectName(QStringLiteral("close_btn"));
        close_btn->setMinimumSize(QSize(150, 30));
        close_btn->setMaximumSize(QSize(80, 16777215));
        close_btn->setFont(font);

        horizontalLayout->addWidget(close_btn);

        horizontalSpacer_4 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_4);


        verticalLayout_4->addWidget(widget);

        verticalSpacer_2 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_4->addItem(verticalSpacer_2);


        retranslateUi(Widget);

        QMetaObject::connectSlotsByName(Widget);
    } // setupUi

    void retranslateUi(QWidget *Widget)
    {
        Widget->setWindowTitle(QApplication::translate("Widget", "Widget", Q_NULLPTR));
        conn_btn->setText(QApplication::translate("Widget", "connect server", Q_NULLPTR));
        port_lab->setText(QApplication::translate("Widget", "port", Q_NULLPTR));
        ip_lab->setText(QApplication::translate("Widget", "ip", Q_NULLPTR));
        send_btn->setText(QApplication::translate("Widget", "send", Q_NULLPTR));
        recv_lab->setText(QApplication::translate("Widget", "recv", Q_NULLPTR));
        recv_massage->setText(QString());
        close_btn->setText(QApplication::translate("Widget", "close", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class Widget: public Ui_Widget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_WIDGET_H

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QUdpSocket>
#include <QTextLayout>

#include "ui_mainwindow.h"

namespace Ui {
    class MainWindow;
}

class MainWindow : public QMainWindow, public Ui::MainWindow {
    Q_OBJECT
    public:
        MainWindow(QWidget *parent = 0);
    private slots:
        //Getting double-click to refresh the message field
        void itemDoubleClick(QListWidgetItem*);
        //Reading incoming message
        void readyRead();
        //Login to chat
        void on_adduser_clicked();
        //Send message to chat
        void on_send_clicked();

private:
        QUdpSocket *sendS;

        QString nick = "";
};
#endif // MAINWINDOW_H

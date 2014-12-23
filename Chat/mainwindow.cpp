#include "mainwindow.h"

#include <QRegExp>
#include <string>

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent) {
    setupUi(this);
    user->setText("enter your name here");
    QString a = " Hello \n enter your name and go chat \n";
    new QListWidgetItem(QPixmap(),a, messager);
    QUdpSocket* tmp = new QUdpSocket(this);
    tmp->bind(QHostAddress::Any, 1234);
    sendS = tmp;
    connect(sendS, SIGNAL(readyRead()), this, SLOT(readyRead()));
    connect(this->users, SIGNAL(itemDoubleClicked(QListWidgetItem*)), this, SLOT(itemDoubleClick(QListWidgetItem*)));
    connect(this->messager, SIGNAL(itemDoubleClicked(QListWidgetItem*)), this, SLOT(itemDoubleClick(QListWidgetItem*)));
}


void MainWindow::itemDoubleClick(QListWidgetItem *item)
{

    message->clear();

    if(item->listWidget() == users)
    {
        message->setText(item->text() + ", ");

    }
    else
    {

        QString s = item->text();
        QString res = "";
        for(int i = 0; i < s.size(); i++)
        {
            if(s[i] == ':')
                break;
            res += s[i];
        }
        message->setText(res + ", ");

    }


}

void MainWindow::readyRead()
{
    for(;;)
    {
    if(sendS->hasPendingDatagrams())
    {
        QByteArray buffer;
        buffer.resize(sendS->pendingDatagramSize());
        QHostAddress sender;
        quint16 port;
        sendS->readDatagram(buffer.data(), buffer.size(), &sender, &port);
        QString line = QString::fromUtf8(buffer).trimmed();
        QString s = line;
        QString nick = "";
        for(int i = 0 ; i < s.size();i++)
        {
            if(s[i] == ':')
                break;
            nick+=s[i];
        }
        bool toShow = true;
        for(int i = 0 ; i < users->count();i++)
        {
            if(users->item((i))->text() == nick)
                toShow = false;
        }
        if(toShow)
            new QListWidgetItem(QPixmap(), nick, users );
        new QListWidgetItem(QPixmap(),line, messager);


    }
    else
        return;
    }
}

void MainWindow::on_adduser_clicked()
{
    if(this->nick !="")
    {
        user->setText("Go chat");
        return;
    }
    if(user->text()=="")
    {
        user->setText("enter your name");
        return;
    }
    this->nick = user->text();

    user->setText("you was added");
    message->setText(this->nick);
    QString toSend = this->nick + ": Hello!";
    QByteArray report;
    report.append(toSend);
    sendS->writeDatagram(report.data(), report.size(), QHostAddress::Broadcast, 1234);
}

void MainWindow::on_send_clicked()
{
    if(this->nick == "")
    {
        message->setText("please enter your name");
        return;
    }
    if(message->toPlainText() == "")
    {
        return;
    }
    QString toSend = this->nick + ": "+ message->toPlainText();
    QByteArray report;
    report.append(toSend);
    sendS->writeDatagram(report.data(), report.size(), QHostAddress::Broadcast, 1234);
    message->setText("");
}

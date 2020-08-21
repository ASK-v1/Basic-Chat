#include <QHostAddress>
#include <QDateTime>
#include <QTextEdit>
#include <QMessageBox>
#include <QDebug>
#include "client/clientwidget.h"
#include "ui_clientwidget.h"


ClientWidget::ClientWidget(QWidget *parent) : QWidget(parent) , ui(new Ui::ClientWidget){


    ui->setupUi(this);
    setWindowTitle(tr("Client"));
    setWindowIcon(QPixmap(":/new/client.png"));


    udpSocket = new QUdpSocket(this);
    if(!udpSocket){

        qDebug() << "udpSpcket Error";
    }


    udpSocket->bind(QHostAddress::AnyIPv4, 1111);
    connect(udpSocket, &QUdpSocket::readyRead, this, &ClientWidget::dealMsg);
    connect(udpSocket, &QTcpSocket::disconnected,[=](){

    udpSocket->close();
    });


    tcpSocket = new QTcpSocket(this);
    if(!tcpSocket){

        qDebug() << "tcpSocket Error";
    }


    connect(tcpSocket, &QTcpSocket::connected, [=](){

        localAddress = tcpSocket->localAddress().toString();
        localTcpPort = tcpSocket->localPort();
        peerAddress = tcpSocket->peerAddress().toString();
        peerTcpPort = tcpSocket->peerPort();
        localUdpPort = udpSocket->localPort();
        peerUdpPort = peerTcpPort + 1;


                QString temp = tr("Connected\n");
                ui->textEditReceive->setText(temp);
            });


}



ClientWidget::~ClientWidget(){

    delete ui;
}


void ClientWidget::on_buttonConnect_clicked(){

    peerAddress = ui->lineEditIP->text();
    peerTcpPort = ui->lineEditPort->text().toInt();
    tcpSocket->connectToHost(QHostAddress(peerAddress), peerTcpPort);
}

void ClientWidget::on_buttonSend_clicked(){


    QString sendData = ui->textEditSend->toPlainText();
    udpSocket->writeDatagram(sendData.toUtf8(), QHostAddress(peerAddress), peerUdpPort);
    ui->textEditSend->clear();
}

void ClientWidget::on_buttonClose_clicked(){

    udpSocket->disconnectFromHost();
    ui->textEditReceive->append(tr("Disconnected"));
}



void ClientWidget::dealMsg(){


    char buf[9999] {0};
    QHostAddress address;
    quint16 port;
    quint32 len = udpSocket->readDatagram(buf, sizeof(buf), &address, &port);


    if(len > 0){

        QString str = QString("[%1:%2] %3").arg(address.toString()).arg(port).arg(buf);
        qDebug() << str;

        ui->textEditReceive->append(tr("Server User %1").arg(QDateTime::currentDateTime().toString("hh:mm::ss")));
        ui->textEditReceive->append(QString(buf));
    }
}

#include <QHostAddress>
#include <QMessageBox>
#include <QDateTime>
#include "server/serverwidget.h"
#include "ui_serverwidget.h"


ServerWidget::ServerWidget(QWidget *parent) : QWidget(parent) , ui(new Ui::ServerWidget){


    ui->setupUi(this);
    setWindowTitle(tr("Server"));
    setWindowIcon(QPixmap(":/new/client.png"));


    udpSocket = new QUdpSocket(this);
    if(!udpSocket){
        qDebug() << "udpSocket Error";
    }


    udpSocket->bind(QHostAddress::AnyIPv4, 8889);

    connect(udpSocket, &QUdpSocket::readyRead, this, &ServerWidget::dealMsg);
    connect(udpSocket, &QTcpSocket::disconnected, [=](){

        udpSocket->close();

    });



    tcpServer = new QTcpServer(this);
    if(!tcpServer){
        qDebug() << "tcpSocket Error";
    }


    if(!tcpServer->listen(QHostAddress::AnyIPv4, 8888)){

        QMessageBox::critical(this, tr("Chat Server"),
        tr("Unable to start the server: %1.").arg(tcpServer->errorString()));
    }


    connect(tcpServer, &QTcpServer::newConnection,[=](){


             tcpSocket = tcpServer->nextPendingConnection();
             localAddress = tcpSocket->localAddress().toString();
             localTcpPort = tcpSocket->localPort();
             peerAddress = tcpSocket->peerAddress().toString();
             peerTcpPort = tcpSocket->peerPort();
             localUdpPort = udpSocket->localPort();
             peerUdpPort = 1111;



        QString temp = tr("Connected\n");

        ui->textEditReceive->setText(temp);


        });
}


ServerWidget::~ServerWidget(){
    delete ui;
}


void ServerWidget::on_buttonSend_clicked(){

    QString sendData = ui->textEditSend->toPlainText();

    udpSocket->writeDatagram(sendData.toUtf8(), QHostAddress(peerAddress), peerUdpPort);
    ui->textEditSend->clear();
 }


void ServerWidget::on_buttonClose_clicked(){

    udpSocket->disconnectFromHost();
    ui->textEditReceive->append(tr("Disconnected"));
}




void ServerWidget::dealMsg(){

    char buf[9999] {0};
    QHostAddress address;
    quint16 port;
    quint64 len = udpSocket->readDatagram(buf, sizeof(buf), &address, &port);

    if(len > 0){

        QString str = QString("[%1:%2] %3").arg(address.toString()).arg(port).arg(buf);
        qDebug() << str;

        ui->textEditReceive->append(tr("Client User %1").arg(QDateTime::currentDateTime().toString("hh:mm::ss")));
        ui->textEditReceive->append(QString(buf));

    }
}




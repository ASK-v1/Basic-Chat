#ifndef SERVERWIDGET_H
#define SERVERWIDGET_H

#include <QWidget>
#include <QTcpServer>
#include <QTcpSocket>
#include <QUdpSocket>

namespace Ui { class ServerWidget; }

class ServerWidget : public QWidget{

    Q_OBJECT

public:
    explicit ServerWidget(QWidget *parent = nullptr);
    ~ServerWidget();


private slots:

    void on_buttonSend_clicked();
    void on_buttonClose_clicked();
    void dealMsg();




private:

    Ui::ServerWidget *ui  {nullptr};
    QUdpSocket *udpSocket {nullptr};
    QTcpServer *tcpServer {nullptr};
    QTcpSocket *tcpSocket {nullptr};
    QString localAddress;
    QString peerAddress;
    quint32  localTcpPort;
    quint32  peerTcpPort;
    quint32  localUdpPort;
    quint32  peerUdpPort;


};

#endif // SERVERWIDGET_H

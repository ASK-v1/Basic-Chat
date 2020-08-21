#ifndef CLIENTWIDGET_H
#define CLIENTWIDGET_H

#include <QWidget>
#include <QTcpSocket>
#include <QUdpSocket>

namespace Ui { class ClientWidget; }

class ClientWidget : public QWidget{

    Q_OBJECT

public:

    explicit ClientWidget(QWidget *parent = nullptr);
    ~ClientWidget();

private slots:
    void on_buttonConnect_clicked();
    void on_buttonSend_clicked();
    void on_buttonClose_clicked();
    void dealMsg();

private:

    Ui::ClientWidget *ui   {nullptr};
    QTcpSocket* tcpSocket  {nullptr};
    QUdpSocket* udpSocket  {nullptr};
    quint32 peerTcpPort;
    quint32 localUdpPort;
    quint32 peerUdpPort;
    quint32 localTcpPort;
    QString localAddress;
    QString peerAddress;


};

#endif // CLIENTWIDGET_H

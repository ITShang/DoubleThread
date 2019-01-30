#include "myrecvthread.h"
#include "gloab.h"
#include <QUdpSocket>
#include <QMutexLocker>
#include <QTimer>

#include <QDebug>

MyrecvThread::MyrecvThread(QObject *parent) : QThread(parent)
{

}

MyrecvThread::~MyrecvThread()
{
    qDebug()<<__FILE__<<__LINE__<<__FUNCTION__<<"\n"
           <<"detroyed "<<this
          <<"\n";
}

void MyrecvThread::run()
{
    QUdpSocket *udpSocket = new QUdpSocket();
    udpSocket->bind(QHostAddress::LocalHost, 7755);

    connect(udpSocket, SIGNAL(readyRead()),
            this, SLOT(readPendingDatagrams()));

    QTimer *t_timer = new QTimer();
    connect(t_timer,SIGNAL(timeout()),
            this,SLOT(wakeOtherThread()));
    t_timer->start(1000*1);

    exec();
}

void MyrecvThread::readPendingDatagrams()
{
    qDebug()<<__FILE__<<__LINE__<<__FUNCTION__<<"\n"
           <<"*************************"
          <<"\n";
    QUdpSocket *udpSocket = qobject_cast<QUdpSocket*>(sender());
    if(udpSocket)
    {
        while (udpSocket->hasPendingDatagrams())
        {
            QByteArray datagram;
            datagram.resize(udpSocket->pendingDatagramSize());
            QHostAddress sender;
            quint16 senderPort;

            udpSocket->readDatagram(datagram.data(), datagram.size(),
                                    &sender, &senderPort);

            processTheDatagram(datagram);
        }
    }
}

void MyrecvThread::wakeOtherThread()
{
    static int countNum = 0;
    countNum++;
    processTheDatagram(QString::number(countNum).toLocal8Bit());
}

void MyrecvThread::processTheDatagram(QByteArray in_data)
{
    QMutexLocker locker(&G_QueneMutex);
    G_RecvQueue.enqueue(in_data);
    G_RecvQueue.enqueue(in_data);
    G_RecvQueue.enqueue(in_data);
    G_RecvQueue.enqueue(in_data);
    G_RecvQueue.enqueue(in_data);

    qDebug()<<__FILE__<<__LINE__<<__FUNCTION__<<"\n"
           <<"G_RecvQueue.size():"<<G_RecvQueue.size()
          <<"\n";
    G_RecvCondition.wakeAll();
}

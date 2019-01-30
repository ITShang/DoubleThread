#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "thread/gloab.h"
#include "thread/mydealthread.h"
#include "thread/myrecvthread.h"

#include <QUdpSocket>
#include <QHostAddress>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    m_pUdpSocket = new QUdpSocket(this);
    startTimer(1000 * 1);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::timerEvent(QTimerEvent *event)
{
    Q_UNUSED(event)
    static int count = 0;
    ++count;
//    qDebug()<<count;
//    m_pUdpSocket->writeDatagram(QString::number(count).toLocal8Bit(),QHostAddress(QHostAddress::LocalHost),7755);
}

void MainWindow::on_pushButton_clicked()
{
    MyrecvThread *t_MyrecvThread = new MyrecvThread();
    t_MyrecvThread->start();

    MyDealThread *t_MyDealThread = new MyDealThread();
    t_MyDealThread->start();
}

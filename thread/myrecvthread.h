#ifndef MYRECVTHREAD_H
#define MYRECVTHREAD_H

#include <QThread>

class MyrecvThread : public QThread
{
    Q_OBJECT
public:
    explicit MyrecvThread(QObject *parent = 0);
    ~MyrecvThread();

protected:
    void run();

signals:

public slots:
    void readPendingDatagrams();
    void wakeOtherThread();

private:
    void processTheDatagram(QByteArray in_data);
};

#endif // MYRECVTHREAD_H

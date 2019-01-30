#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
class QUdpSocket;

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

protected:
    void timerEvent(QTimerEvent *event);

private slots:
    void on_pushButton_clicked();

private:
    Ui::MainWindow *ui;
    QUdpSocket *m_pUdpSocket ;
};

#endif // MAINWINDOW_H

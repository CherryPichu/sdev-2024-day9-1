#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <qtcpsocket.h>
#include <QSslSocket>
#include <QUdpSocket>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    QTcpSocket socket_;
    QUdpSocket socket_udp;
    QSslSocket socket_ssl;



public slots:
    void doConnected();
    void doDisConnected();
    void doReadyRead();
    void refresh();




private slots:
    void on_display_result_blockCountChanged(int newBlockCount);

    void on_btn_disconnect_clicked();

    void on_btn_clear_clicked();

    void on_btn_connect_clicked();

    void on_btn_send_clicked();

    void on_btn_tcp_clicked();

    void on_btn_ssl_clicked();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H

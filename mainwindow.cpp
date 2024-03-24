#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "QString"
#include <array>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{

    ui->setupUi(this);

    QObject::connect(&socket_ssl, &QAbstractSocket::connected, this, &MainWindow::doConnected ); // 옵저버 패턴
    QObject::connect(&socket_ssl, &QAbstractSocket::disconnected, this, &MainWindow::doDisConnected ); // 옵저버 패턴
    QObject::connect(&socket_ssl, &QAbstractSocket::readyRead, this, &MainWindow::doReadyRead ); // 옵저버 패턴

    QObject::connect(&socket_, &QAbstractSocket::connected, this, &MainWindow::doConnected ); // 옵저버 패턴
    QObject::connect(&socket_, &QAbstractSocket::disconnected, this, &MainWindow::doDisConnected ); // 옵저버 패턴
    QObject::connect(&socket_, &QAbstractSocket::readyRead, this, &MainWindow::doReadyRead ); // 옵저버 패턴

}

void MainWindow::doConnected(){
    ui->edit_result->insertPlainText("Connected\n");
    refresh();
}

void MainWindow::doDisConnected() {
    ui->edit_result->insertPlainText("Disconnected\n");
    refresh();
}

void MainWindow::doReadyRead(){
    short port = ui->edit_port->text().toShort();
    switch(port) {
    case 80 :
        ui->edit_result->insertPlainText(socket_.readAll());
        break;
    case 443 :
        ui->edit_result->insertPlainText(socket_ssl.readAll());
        break;
    }


}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_display_result_blockCountChanged(int newBlockCount){

}


void MainWindow::refresh(){
    if(socket_.state() == QAbstractSocket::ConnectedState || socket_ssl.state() == QAbstractSocket::ConnectedState){
        ui->btn_connect->setEnabled(false);
        ui->btn_disconnect->setEnabled(true);
    }else{
        ui->btn_connect->setEnabled(true);
        ui->btn_disconnect->setEnabled(false);
    }

}


void MainWindow::on_btn_disconnect_clicked()
{
    short port = ui->edit_port->text().toShort();
    switch(port) {
    case 80 :
        socket_.close();
        break;
    case 443 :
        socket_ssl.close();
        break;
    }


    // socket_.disconnect(ui->edit_host->text());
}


void MainWindow::on_btn_clear_clicked()
{
    ui->edit_result->clear();
}


void MainWindow::on_btn_connect_clicked()
{
    short port = ui->edit_port->text().toShort();
    switch(port) {
        case 80 : // this will be good when changed to constant type. but we have short time.
            // if you try it. this code will be efficiently. I encouaged it.
            // why I can't use korean keyboard? Damn it!
            // I can't write good english bb....
            // example. "80" -> HTTP_PORT
            socket_.connectToHost(ui->edit_host->text(), ui->edit_port->text().toShort());
            break;
        case 443 :
            socket_ssl.connectToHostEncrypted(ui->edit_host->text(), ui->edit_port->text().toShort());
            break;
    }
}


void MainWindow::on_btn_send_clicked()
{
    short port = ui->edit_port->text().toShort();
    switch(port) {
    case 80 :
        socket_.write(ui->edit_plain->toPlainText().toUtf8());
        break;
    case 443 :
        socket_ssl.write(ui->edit_plain->toPlainText().toUtf8());
        break;
    }

}


void MainWindow::on_btn_tcp_clicked()
{
    QString str = QString::number(80);
    ui->edit_port->setText(str);
}


void MainWindow::on_btn_ssl_clicked()
{
    QString str = QString::number(443);
    ui->edit_port->setText(str);
}


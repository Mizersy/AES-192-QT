#include "mainwindow_init.h"
#include "ui_mainwindow_init.h"
#include "mainwindow.h"
#include "mainwindow_decrypt.h"

MainWindow_init::MainWindow_init(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow_init)
{
    ui->setupUi(this);
    this->setWindowTitle("AES加解密程序");
}

MainWindow_init::~MainWindow_init()
{
    delete ui;
}

void MainWindow_init::on_encrypt_clicked()
{
    MainWindow *w = new MainWindow();
    w->show();
}

void MainWindow_init::on_Decrypt_clicked()
{
    MainWindow_decrypt *w = new MainWindow_decrypt();
    w->show();
}

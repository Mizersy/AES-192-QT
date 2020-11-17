#ifndef MAINWINDOW_INIT_H
#define MAINWINDOW_INIT_H

#include <QMainWindow>

namespace Ui {
class MainWindow_init;
}

class MainWindow_init : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow_init(QWidget *parent = nullptr);
    ~MainWindow_init();

private slots:
    void on_encrypt_clicked();

    void on_Decrypt_clicked();

private:
    Ui::MainWindow_init *ui;
};

#endif // MAINWINDOW_INIT_H

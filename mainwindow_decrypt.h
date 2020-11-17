#ifndef MAINWINDOW_DECRYPT_H
#define MAINWINDOW_DECRYPT_H

#include <QMainWindow>

namespace Ui {
class MainWindow_decrypt;
}

class MainWindow_decrypt : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow_decrypt(QWidget *parent = nullptr);
    ~MainWindow_decrypt();

private slots:
    void on_Decrypt_clicked();
    QString Decrypt(QString textIn,QString textKey);
    void generate_key();
    void generate_T(int C);
    void copy_c(int C);
    int myPow(int x,int y);
    void ARK(int round);
    void IMC();
    void ISR();
    void IBS();
    int mymul(int x,int y);
    int mul2(int y);

private:
    Ui::MainWindow_decrypt *ui;
};

#endif // MAINWINDOW_DECRYPT_H

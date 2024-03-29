#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
//#include <bits/stdc++.h>
//using namespace std;
//明文1：00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00
//密钥1：00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00
//密文1：aa e0 69 92 ac bf 52 a3 e8 f4 a9 6e c9 30 0b d7
//明文2：00 11 22 33 44 55 66 77 88 99 aa bb cc dd ee ff
//密钥2：00 01 02 03 04 05 06 07 08 09 0a 0b 0c 0d 0e 0f 10 11 12 13 14 15 16 17
//密文2：dd a9 7c a4 86 4c df e0 6e af 70 a0 ec 0d 71 91
int matrix[4][4];
int key_matrix[4][52];
const int D = 1<<9;
const int S[16][16] = {0x63, 0x7c, 0x77, 0x7b, 0xf2, 0x6b, 0x6f, 0xc5, 0x30, 0x01, 0x67, 0x2b, 0xfe, 0xd7, 0xab, 0x76,
                       0xca, 0x82, 0xc9, 0x7d, 0xfa, 0x59, 0x47, 0xf0, 0xad, 0xd4, 0xa2, 0xaf, 0x9c, 0xa4, 0x72, 0xc0,
                       0xb7, 0xfd, 0x93, 0x26, 0x36, 0x3f, 0xf7, 0xcc, 0x34, 0xa5, 0xe5, 0xf1, 0x71, 0xd8, 0x31, 0x15,
                       0x04, 0xc7, 0x23, 0xc3, 0x18, 0x96, 0x05, 0x9a, 0x07, 0x12, 0x80, 0xe2, 0xeb, 0x27, 0xb2, 0x75,
                       0x09, 0x83, 0x2c, 0x1a, 0x1b, 0x6e, 0x5a, 0xa0, 0x52, 0x3b, 0xd6, 0xb3, 0x29, 0xe3, 0x2f, 0x84,
                       0x53, 0xd1, 0x00, 0xed, 0x20, 0xfc, 0xb1, 0x5b, 0x6a, 0xcb, 0xbe, 0x39, 0x4a, 0x4c, 0x58, 0xcf,
                       0xd0, 0xef, 0xaa, 0xfb, 0x43, 0x4d, 0x33, 0x85, 0x45, 0xf9, 0x02, 0x7f, 0x50, 0x3c, 0x9f, 0xa8,
                       0x51, 0xa3, 0x40, 0x8f, 0x92, 0x9d, 0x38, 0xf5, 0xbc, 0xb6, 0xda, 0x21, 0x10, 0xff, 0xf3, 0xd2,
                       0xcd, 0x0c, 0x13, 0xec, 0x5f, 0x97, 0x44, 0x17, 0xc4, 0xa7, 0x7e, 0x3d, 0x64, 0x5d, 0x19, 0x73,
                       0x60, 0x81, 0x4f, 0xdc, 0x22, 0x2a, 0x90, 0x88, 0x46, 0xee, 0xb8, 0x14, 0xde, 0x5e, 0x0b, 0xdb,
                       0xe0, 0x32, 0x3a, 0x0a, 0x49, 0x06, 0x24, 0x5c, 0xc2, 0xd3, 0xac, 0x62, 0x91, 0x95, 0xe4, 0x79,
                       0xe7, 0xc8, 0x37, 0x6d, 0x8d, 0xd5, 0x4e, 0xa9, 0x6c, 0x56, 0xf4, 0xea, 0x65, 0x7a, 0xae, 0x08,
                       0xba, 0x78, 0x25, 0x2e, 0x1c, 0xa6, 0xb4, 0xc6, 0xe8, 0xdd, 0x74, 0x1f, 0x4b, 0xbd, 0x8b, 0x8a,
                       0x70, 0x3e, 0xb5, 0x66, 0x48, 0x03, 0xf6, 0x0e, 0x61, 0x35, 0x57, 0xb9, 0x86, 0xc1, 0x1d, 0x9e,
                       0xe1, 0xf8, 0x98, 0x11, 0x69, 0xd9, 0x8e, 0x94, 0x9b, 0x1e, 0x87, 0xe9, 0xce, 0x55, 0x28, 0xdf,
                       0x8c, 0xa1, 0x89, 0x0d, 0xbf, 0xe6, 0x42, 0x68, 0x41, 0x99, 0x2d, 0x0f, 0xb0, 0x54, 0xbb, 0x16};
const int matrix_a[4][4] = {2,3,1,1,
                            1,2,3,1,
                            1,1,2,3,
                            3,1,1,2};
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setWindowTitle("解密程序");
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pushButton_clicked()
{
    QString textIn = ui->text_in->toPlainText();
    QString textKey = ui->key->toPlainText();

    QString textOut = AES(textIn,textKey);
    ui->text_out->setText(textOut);

}

int MainWindow::myPow(int x,int y){
    int ret = 1;
    for (int i = 0;i < y;++i){
        ret *= x;
    }
    return ret;
}

//生成T
void MainWindow::generate_T(int C){
    copy_c(C);
    for (int i = 0;i < 3;++i){
        qSwap(key_matrix[i][C],key_matrix[i+1][C]);
    }
    for (int i = 0;i < 4;++i){
        key_matrix[i][C] = S[key_matrix[i][C]/D][key_matrix[i][C]%D];
    }

    //一开始看课件以为这里是10的幂次，没想到课件里是二进制...
    key_matrix[0][C] ^= myPow(2,(C-6)/6);
}

void MainWindow::copy_c(int C){
    for (int i = 0;i < 4;++i){
        key_matrix[i][C] = key_matrix[i][C-1];
    }
}

//生成密钥
void MainWindow::generate_key(){
    for (int c = 6;c < 52;++c){
        if (c%6 == 0){//c整除6
            generate_T(c);
        }else{
            copy_c(c);
        }
        for (int i = 0;i < 4;++i){
            key_matrix[i][c] ^= key_matrix[i][c-6];
        }
    }
}

void MainWindow::BS(){
    for (int i = 0;i < 4;++i){
        for (int j = 0;j < 4;++j){
            matrix[i][j] = S[matrix[i][j]/D][matrix[i][j]%D];
        }
    }
}

void MainWindow::ARK(int round){
    for (int i = 0;i < 4;++i){
        for (int j = 0;j < 4;++j){
            matrix[i][j] ^= key_matrix[i][j+round*4];
        }
    }
}

void MainWindow::SR(){
    for (int i = 0;i < 4;++i){
        for (int j = 0;j < i;++j){
            for (int k = 0;k < 3;++k){
                qSwap(matrix[i][k],matrix[i][k+1]);
            }
        }
    }
}


int mul2(int y){
    if (y&128){
        return (((y<<1)^283));
    }else return ((y<<1));
}

int mymul(int x,int y){
    if (x == 1) return y;
    if (x == 2) return mul2(y);
    else return mul2(y)^y;
}

void MainWindow::MC(){
    int matrix_tmp[4][4];
    for (int i = 0;i < 4;++i){
        for (int j = 0;j < 4;++j){
            int tmp = 0;
            for (int k = 0;k < 4;++k){
                tmp ^= mymul(matrix_a[i][k],matrix[k][j]);
            }
            matrix_tmp[i][j] = tmp;
        }
    }
    for (int i = 0;i < 4;++i){
        for (int j = 0;j < 4;++j){
            matrix[i][j] = matrix_tmp[i][j];
        }
    }
}

QString MainWindow::AES(QString textIn,QString textKey){
    QStringList textInList = textIn.split(" ");
    QStringList textKeyList = textKey.split(" ");
    for(int i = 0;i < 16;++i){//明文字符转数字
        matrix[i%4][i/4] = textInList[i].toInt(nullptr,16);
    }
    for (int i = 0;i < 24;++i){//密钥字符转数字
        key_matrix[i%4][i/4] = textKeyList[i].toInt(nullptr,16);
    }
    generate_key();

    ARK(0);
    for (int i = 1;i <= 12;++i){
        BS();

        SR();

        if (i != 12) MC();

        ARK(i);
    }
    QStringList retList;
    for (int j = 0;j < 4;++j){
        for (int i = 0;i < 4;++i){
            retList.append(QString("%1").arg(matrix[i][j],2,16,QLatin1Char('0')));
        }
    }
    QString retQString = retList.join(" ");
    return retQString;
}


#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFileDialog>
#include<iostream>


int getMaxNumPix(int *x, int size){
    int maximum = 0;
    for(int i = 0; i < size; i++){
        if (maximum < x[i]){
            maximum = x[i];
        }
    }
    return maximum;
}

void setWhite(QImage &I){
    for (int y = 0; y < I.height(); y++) {
        QRgb *pixel_src = (QRgb*)I.scanLine(y);

        for (int x = 0; x < I.width(); x++) {

            pixel_src[x] = qRgb(255, 255, 255);
        }
    }
}


void drawLine(QImage &I, unsigned char value, int height){
    for (unsigned char y = 0; y < I.height(); y++) {
        QRgb *pixel_src = (QRgb*)I.scanLine(y);

        for (unsigned char x = 0; x < I.width(); x++) {
            if(x == value && y > I.height() - height){

                pixel_src[x] = qRgb(1, 1, 1);
            }
        }
    }
}

int normalizeValue(int *x, int size, unsigned char value){
    float out = (float)x[value];
    out = (out / size) * 255;
    return (int)out;
}


void getRGBarrays(const QImage &src,int *red,int *green,int *blue){

    for (int y = 0; y < src.height(); y++) {
        QRgb *pixel_src = (QRgb*)src.scanLine(y);

        for (int x = 0; x < src.width(); x++) {
            unsigned char r = qRed(pixel_src[x]);
            unsigned char g = qGreen(pixel_src[x]);
            unsigned char b = qBlue(pixel_src[x]);


            red[r] += 1;
            green[g] += 1;
            blue[b] += 1;
        }
    }

}


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::openImage() {
    QString fileName = QFileDialog::getOpenFileName();

    if (!fileName.isNull()) {
        originalImage.load(fileName);
        ui->image->setPixmap(QPixmap::fromImage(originalImage));
    }

    int *red = new int[256];
    int *green = new int[256];
    int *blue = new int[256];


    getRGBarrays(originalImage,red,green,blue);


    QImage histRed = QImage (255, 255, QImage::Format_RGB32);
    QImage histGreen = QImage (255, 255, QImage::Format_RGB32);
    QImage histBlue = QImage (255, 255, QImage::Format_RGB32);

    setWhite(histRed);
    setWhite(histGreen);
    setWhite(histBlue);

    for (unsigned char i = 0; i < 255; i++){

        float heightR = normalizeValue(red, getMaxNumPix(red,255), i);
        float heightG = normalizeValue(green, getMaxNumPix(green,255), i);
        float heightB = normalizeValue(blue, getMaxNumPix(green,255), i);

        std::cout << heightR << " " << heightG << " " << std::endl;

        drawLine(histRed, i, heightR);
        drawLine(histGreen, i,heightG);
        drawLine(histBlue, i,heightB);

    }


    ui->histRed->setPixmap(QPixmap::fromImage(histRed));
    ui->histGreen->setPixmap(QPixmap::fromImage(histGreen));
    ui->histBlue->setPixmap(QPixmap::fromImage(histBlue));

}

void MainWindow::on_actionOpen_triggered()
{
    openImage();
}


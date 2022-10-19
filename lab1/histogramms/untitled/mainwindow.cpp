#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFileDialog>
#include<iostream>




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

float getHeightOfHist(unsigned char *x, int size, unsigned char value){
    float out = 0.0f;
    for (int i = 0; i < size; i++){
        if(x[i] == value){
            out += 1;
        }
    }

    out = (out / size) * 255;
    std::cout << out << std::endl;
    return out;
}


void getRGBarrays(const QImage &src,unsigned char *red,unsigned char *green,unsigned char *blue){
    int pixel_count = src.height() * src.width();

    red = new unsigned char[pixel_count];
    green = new unsigned char[pixel_count];
    blue = new unsigned char[pixel_count];

    for (int y = 0; y < src.height(); y++) {
        QRgb *pixel_src = (QRgb*)src.scanLine(y);

        for (int x = 0; x < src.width(); x++) {
            unsigned char r = qRed(pixel_src[x]);
            unsigned char g = qGreen(pixel_src[x]);
            unsigned char b = qBlue(pixel_src[x]);


            red[y * src.width() + x] = r;
            green[y * src.width() + x] = g;
            blue[y * src.width() + x] = b;
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

    unsigned char *red;
    unsigned char *green;
    unsigned char *blue;
    int imgSize = originalImage.height() * originalImage.width();

    getRGBarrays(originalImage,red,green,blue);


    QImage histRed = QImage (255, 255, QImage::Format_RGB32);
    QImage histGreen = QImage (255, 255, QImage::Format_RGB32);
    QImage histBlue = QImage (255, 255, QImage::Format_RGB32);

    setWhite(histRed);
    setWhite(histGreen);
    setWhite(histBlue);

    for (unsigned char i = 0; i < 255; i++){

        float heightR = getHeightOfHist(red, imgSize, i);
        float heightG = getHeightOfHist(green, imgSize, i);
//        float heightB = getHeightOfHist(blue, imgSize, i);

        std::cout << heightR << " " << heightG << " " << std::endl;

        drawLine(histRed, i, (int)heightR);
        drawLine(histGreen, i,(int)heightG);
//        drawLine(histBlue, i, heightB);

    }


    ui->histRed->setPixmap(QPixmap::fromImage(histRed));
    ui->histGreen->setPixmap(QPixmap::fromImage(histGreen));
    ui->histBlue->setPixmap(QPixmap::fromImage(histBlue));

}

void MainWindow::on_actionOpen_triggered()
{
    openImage();
}


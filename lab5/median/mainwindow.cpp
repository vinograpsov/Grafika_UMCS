#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFileDialog>
#include <iostream>
#include <cmath>

int get_vector_pos(int i, int r){
    return r + i;
}


QImage black_borders_img(const QImage& src, int r){
    QImage border(src.width() + 2*r, src.height() +2*r, src.format());
    for(int y = 0; y < src.height(); y++){
        uchar* pixel_src = (uchar*)src.scanLine(y);
        uchar* pixel_dst = (uchar*)border.scanLine(y+r) + 4*r;
        memcpy(pixel_dst, pixel_src, 4*src.width());
    }
    return border;

}


QImage line_borders_img(const QImage& src, int r){
    QImage border(src.width() + 2*r, src.height() +2*r, src.format());

    for(int y = 0; y < src.height(); y++){
        uchar* pixel_src = (uchar*)src.scanLine(y);
        uchar* pixel_dst = (uchar*)border.scanLine(y+r) + 4*r;
        memcpy(pixel_dst, pixel_src, 4*src.width());
    }

    for(int y = r; y < border.height() - r; y++){


        QRgb *pixel_src = (QRgb*)src.scanLine(y - r);
        QRgb *pixel_dst = (QRgb*)border.scanLine(y);

        for(int x = 0; x < border.width(); x++){
            if (x < r){
                unsigned char r = qRed(pixel_src[0]);
                unsigned char g = qGreen(pixel_src[0]);
                unsigned char b = qBlue(pixel_src[0]);
                pixel_dst[x] = qRgb(r,g,b);
            }
            else if (x >= border.width() - r){
                unsigned char r = qRed(pixel_src[src.width() - 1]);
                unsigned char g = qGreen(pixel_src[src.width()- 1]);
                unsigned char b = qBlue(pixel_src[src.width()- 1]);
                pixel_dst[x] = qRgb(r,g,b);
            }
        }
    }

    for(int y = 0; y < border.height(); y++){
        if(y < r){
            uchar* pixel_src = (uchar*)border.scanLine(r);
            uchar* pixel_dst = (uchar*)border.scanLine(y);
            memcpy(pixel_dst, pixel_src, 4*border.width());
        }
        if(y >= border.height() - r){
            uchar* pixel_src = (uchar*)border.scanLine(border.height() - r - 1);
            uchar* pixel_dst = (uchar*)border.scanLine(y);
            memcpy(pixel_dst, pixel_src, 4*border.width());
        }
    }


    return border;
}

std::vector<uchar> insertionSort(std::vector<uchar> arr)
{
    int i, key, j;
    for (i = 1; i < arr.size(); i++)
    {
        key = arr[i];
        j = i - 1;
        while (j >= 0 && arr[j] > key)
        {
            arr[j + 1] = arr[j];
            j = j - 1;
        }
        arr[j + 1] = key;
    }
    return arr;

}

unsigned char returnMedInVector(std::vector<uchar> arr){
    arr = insertionSort(arr);
    uchar mode = arr.size() % 2;
    if(mode == 0){
        return (arr[arr.size() / 2] + arr[arr.size() / 2 + 1]) / 2;
    }
    else{
        return arr[arr.size() / 2 + 1];
    }
}

void medianMasking(const QImage& src, QImage& dst, int r){

    QImage tempImage = line_borders_img(src,r);

    for(int y = 0; y < src.height(); y++){

        QRgb *pixel_dst = (QRgb*)dst.scanLine(y);

        if(r > 1){
        for(int x = 0; x < src.width(); x++){

            std::vector<uchar> redVec;
            std::vector<uchar> greenVec;
            std::vector<uchar> blueVec;

            for(int iy = -r; iy <=r;iy++){

                QRgb *pixel_border = (QRgb*)tempImage.scanLine(y + iy +r );

                for(int ix = -r; ix <=r;ix++){

                    redVec.push_back(qRed(pixel_border[x+ix + r]));
                    greenVec.push_back(qGreen(pixel_border[x+ix + r]));
                    blueVec.push_back(qBlue(pixel_border[x+ix + r]));

                }

            }
            pixel_dst[x] = qRgb(returnMedInVector(redVec),returnMedInVector(greenVec),returnMedInVector(blueVec));
        }
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



void MainWindow::openImage(){
    QString fileName = QFileDialog::getOpenFileName();

    if (!fileName.isNull()) {
        originalImage.load(fileName);
        processImage = originalImage;
        ui->image->setPixmap(QPixmap::fromImage(originalImage));
    }

//    processImage = line_borders_img(originalImage, 20);
//    processImage = black_borders_img(originalImage, 20);
//    ui->border_image->setPixmap(QPixmap::fromImage(processImage));

}

void MainWindow::on_Open_triggered()
{
    openImage();
}

void MainWindow::on_horizontalSlider_valueChanged(int value)
{
        medianMasking(originalImage,processImage,value);
        ui->image->setPixmap(QPixmap::fromImage(processImage));
}


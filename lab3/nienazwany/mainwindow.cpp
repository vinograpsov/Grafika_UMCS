#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFileDialog>
#include <iostream>

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


std::vector<int> getMaskSharp(int r){
    std::vector<int> out;
    int d = 2 * r + 1;
    if (r == 0){
        out.push_back(1);
        return out;
    }
    for(int i = 0; i < d * d; i++){
        if(i == d * (d / 2) + r){
            out.push_back(d*d);
        }
        else{
            out.push_back(-1);
        }
    }
    return out;
}

std::vector<int> getMaskBorders(int r){
    std::vector<int> out;
    if (r == 0){
        out.push_back(1);
        return out;
    }
    int d = 2 * r + 1;
    for(int i = 0; i < d * d; i++){
        if(i == d * (d / 2) + r){
            out.push_back(d*d - 1);
        }
        else{
            out.push_back(-1);
        }
    }
    return out;
}

std::vector<int> getMaskBlur(int r){
    std::vector<int> out;

    if (r == 0){
        out.push_back(1);
        return out;
    }
    int d = 2 * r + 1;
    for(int i = 0; i < d * d; i++){
        out.push_back(1);
    }
    return out;
}



int get_vector_pos(int i, int r){
    return r + i;
}




void conv2d(const QImage& src, QImage& dst,const std::vector<int>& mask, int r){

    QImage tempImage = line_borders_img(src,r);
//    QImage tempImage = black_borders_img(src,r);

    for(int y = 0; y < src.height(); y++){

        QRgb *pixel_dst = (QRgb*)dst.scanLine(y);


        for(int x = 0; x < src.width(); x++){

            int rr = 0;
            int gg = 0;
            int bb = 0;

            for(int iy = -r; iy <=r;iy++){

                QRgb *pixel_border = (QRgb*)tempImage.scanLine(y + iy +r );

                for(int ix = -r; ix <=r;ix++){

                    int tmp_x, tmp_y;

                    tmp_x = get_vector_pos(ix,r);
                    tmp_y = get_vector_pos(iy,r);


                    rr += qRed(pixel_border[x+ix + r]) * mask[tmp_x + (r * 2 + 1) * tmp_y];
                    gg += qGreen(pixel_border[x+ix + r]) * mask[tmp_x + (r * 2 + 1) * tmp_y];
                    bb += qBlue(pixel_border[x+ix + r]) * mask[tmp_x + (r * 2 + 1) * tmp_y];
                }

            }

            int mask_sum = 0;
            mask_sum = std::accumulate(mask.begin(), mask.end(), 0);


            if (mask_sum == 0) mask_sum = 1;

            rr = clamp<int>((float)rr / (float)mask_sum,0,255);
            gg = clamp<int>((float)gg / (float)mask_sum,0,255);
            bb = clamp<int>((float)bb / (float)mask_sum,0,255);

            pixel_dst[x] = qRgb(rr,gg,bb);
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
        conv2d(originalImage,processImage,getMaskBlur(value),value);
        ui->image->setPixmap(QPixmap::fromImage(processImage));
}


#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFileDialog>
#include <iostream>
#include <cmath>

float get_sigma(int r){
    if(r == 0){
        return 1;
    }
    else{
        return (float)r * 2.0f / 6.0f;
    }
}

std::vector<float> normalise(std::vector<float> matrix){
    float super_value = 0;

    for(int i = 0; i < matrix.size(); i++){
        super_value += matrix[i];
    }


    for(int i = 0; i < matrix.size(); i++){
        matrix[i] /= super_value;
    }

    return matrix;

}


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


float get_super_hard_exp_2d(int x, int y, float sigma){
    float power_of_exp = ((float)(pow(x,2) + pow(y,2)) / (float)(2 * pow(sigma,2)));
    return exp(-power_of_exp);
}

float return_point_gauss_2d(int x, int y, float sigma){
    return (1 / (float)(2 * M_PI * pow(sigma,2))) * get_super_hard_exp_2d(x,y,sigma);
}

std::vector<float> get2DMaskBlurGaus(int r){
    std::vector<float> out;


    float sigma = get_sigma(r);


    if (r == 0){
        out.push_back(1);
        return out;
    }


    for(int y = -r; y <= r; y++){
        for(int x = -r; x <= r; x++){
            out.push_back(return_point_gauss_2d(x,y,sigma));
        }
    }


    for(int j = 0; j < out.size(); j++){
        if(j % (r * 2 + 1) == 0){
            std::cout << std::endl;
        }
        std::cout << out[j] << " ";
    }

    std::cout << std::endl << out.size() << std::endl;

    return out;
}

float get_super_hard_exp_1d(int x,float sigma){
    float power_of_exp = (float)std::pow(x,2) / (float)(2 * std::pow(sigma,2));
    return exp(-power_of_exp);
}

float return_point_gauss_1d(int x, float sigma){
    return (1.0f / (std::pow((2.0f * M_PI + sigma),0.5f))) * get_super_hard_exp_1d(x,sigma);
}

std::vector<float> get1DMaskBlurGaus(int r){
    std::vector<float> out;

    float sigma = get_sigma(r);

    for(int x = -r; x <= r; x++){
        out.push_back(return_point_gauss_1d(x,sigma));
    }

    out = normalise(out);

    for(int j = 0; j < out.size(); j++){
        std::cout << out[j] << " ";
    }
    std::cout << std::endl << out.size() << std::endl;
    return out;
}


void conv2d(const QImage& src, QImage& dst,const std::vector<float>& mask, int r){

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
 // ???????????????????????????????????????????????? maska xz cio
            rr = clamp<int>((float)rr / (float)mask_sum,0,255);
            gg = clamp<int>((float)gg / (float)mask_sum,0,255);
            bb = clamp<int>((float)bb / (float)mask_sum,0,255);

            pixel_dst[x] = qRgb(rr,gg,bb);
        }
    }
}


void conv1d(const QImage& src, QImage& dst,const std::vector<float>& mask, int r){

    QImage tempImage = line_borders_img(src,r);
    if(r > 0){
        for(int y = 0; y < src.height(); y++){

            int rr = 0;
            int gg = 0;
            int bb = 0;

            QRgb *pixel_dst = (QRgb*)dst.scanLine(y);


            for(int x = 0; x < src.width(); x++){

                std::vector<uchar> redVec;
                std::vector<uchar> greenVec;
                std::vector<uchar> blueVec;

                QRgb *pixel_border = (QRgb*)tempImage.scanLine(y + r);

                for(int ix = -r; ix <=r;ix++){

                    int tmp_x = get_vector_pos(ix,r);

                    rr += qRed(pixel_border[x+ix + r]) * mask[tmp_x];
                    gg += qGreen(pixel_border[x+ix + r]) * mask[tmp_x];
                    bb += qBlue(pixel_border[x+ix + r]) * mask[tmp_x];


                }

//                int mask_sum = 0;
//                mask_sum = std::accumulate(mask.begin(), mask.end(), 0);


//                if (mask_sum == 0) mask_sum = 1;

//                rr = clamp<int>((float)rr / (float)mask_sum,0,255);
//                gg = clamp<int>((float)gg / (float)mask_sum,0,255);
//                bb = clamp<int>((float)bb / (float)mask_sum,0,255);

//                rr = clamp<int>((float)rr ,0,255);
//                gg = clamp<int>((float)gg ,0,255);
//                bb = clamp<int>((float)bb ,0,255);
                pixel_dst[x] = qRgb(rr,gg,bb);
            }
        }
        for(int y = 0; y < src.height(); y++){

            int rr = 0;
            int gg = 0;
            int bb = 0;

            QRgb *pixel_dst = (QRgb*)dst.scanLine(y);


            for(int x = 0; x < src.width(); x++){

                std::vector<uchar> redVec;
                std::vector<uchar> greenVec;
                std::vector<uchar> blueVec;

                for(int iy = -r; iy <=r;iy++){

                    QRgb *pixel_border = (QRgb*)tempImage.scanLine(y + iy + r);

                    int tmp_y = get_vector_pos(iy,r);

                    rr += qRed(pixel_border[x + r]) * mask[tmp_y];
                    gg += qGreen(pixel_border[x + r]) * mask[tmp_y];
                    bb += qBlue(pixel_border[x + r]) * mask[tmp_y];

                }

//                int mask_sum = 0;
//                mask_sum = std::accumulate(mask.begin(), mask.end(), 0);


//                if (mask_sum == 0) mask_sum = 1;

//                rr = clamp<int>((float)rr / (float)mask_sum,0,255);
//                gg = clamp<int>((float)gg / (float)mask_sum,0,255);
//                bb = clamp<int>((float)bb / (float)mask_sum,0,255);

//                rr = clamp<int>((float)rr, 0,255);
//                gg = clamp<int>((float)gg ,0,255);
//                bb = clamp<int>((float)bb ,0,255);
                pixel_dst[x] = qRgb(rr,gg,bb);
            }
        }
    }
    else{
        for(int y = 0; y < src.height(); y++){
            QRgb *pixel_dst = (QRgb*)dst.scanLine(y);
            QRgb *pixel_src = (QRgb*)src.scanLine(y);
            for(int x = 0; x < src.width(); x++){

                unsigned char r = qRed(pixel_src[x]);
                unsigned char g = qGreen(pixel_src[x]);
                unsigned char b = qBlue(pixel_src[x]);
                pixel_dst[x] = qRgb(r,g,b);
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
        conv1d(originalImage,processImage,get1DMaskBlurGaus(value),value);

        get1DMaskBlurGaus(value);
        ui->image->setPixmap(QPixmap::fromImage(processImage));
}

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFileDialog>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

void scaleImage(const QImage& src, QImage& dst,float s){
    int w = src.width() * s;
    int h = src.height() * s;
    dst = QImage(w,h,src.format());

    for(int y = 0; y < src.height(); y++){
        for(int x = 0; x < src.width(); x++){
//            int xp = round((float)x / (float)s);
//            int yp = round((float)y / (float)s);

            int xp = round(x * s);
            int yp = round(y * s);


            QRgb *pixel_src = (QRgb*)src.scanLine(y);
            QRgb *pixel_dst = (QRgb*)dst.scanLine(yp);


            uchar r = qRed(pixel_src[x]);
            uchar g = qGreen(pixel_src[x]);
            uchar b = qBlue(pixel_src[x]);

            pixel_dst[xp] = qRgb(r,g,b);

        }
    }
}

void rotateImage(const QImage& src, QImage& dst,float a){
    int w = src.width();
    int h = src.height();
    dst = QImage(w,h,src.format());
    dst.fill(0);

    for(int y = 0; y < src.height(); y++){
        for(int x = 0; x < src.width(); x++){
            float xp = x*cos(-a) - y* sin(-a);
            float yp = x*sin(-a) + y* cos(-a);

            int xd = abs(round(xp));
            int yd = abs(round(yp));

            QRgb *pixel_src = (QRgb*)src.scanLine(y);
            QRgb *pixel_dst = (QRgb*)dst.scanLine(yd);


            uchar r = qRed(pixel_src[x]);
            uchar g = qGreen(pixel_src[x]);
            uchar b = qBlue(pixel_src[x]);

            pixel_dst[xd] = qRgb(r,g,b);

        }
    }
}

void invert(float matrix[9], float *inv[]){
    (*inv)[0] = matrix[4] * matrix[8] - matrix[5] * matrix[7];
    (*inv)[1] = -(matrix[3] * matrix[8] - matrix[5] * matrix[6]);
    (*inv)[2] = matrix[3] * matrix[7] - matrix[4] * matrix[6];
    (*inv)[3] = -(matrix[1] * matrix[8] - matrix[2] * matrix[7]);
    (*inv)[4] = matrix[0] * matrix[8] - matrix[2] * matrix[6];
    (*inv)[5] = -(matrix[0] * matrix[7] - matrix[1] * matrix[6]);
    (*inv)[6] = matrix[1] * matrix[5] - matrix[2] * matrix[5];
    (*inv)[7] = -(matrix[0] * matrix[5] - matrix[2] * matrix[3]);
    (*inv)[8] = matrix[0] * matrix[4] - matrix[1] * matrix[3];
}


void affineImage(const QImage& src, QImage& dst,float matrix[9]){
    int w = src.width();
    int h = src.height();
    dst = QImage(w,h,src.format());
    dst.fill(0);

    float *inv = new float[9];

    invert(matrix,&inv);

    for(int y = 0; y < src.height(); y++){
        for(int x = 0; x < src.width(); x++){
            int xs = x * inv[0] + y * inv[1] + inv[2];
            int ys = x * inv[3] + y * inv[4] + inv[5];


            QRgb *pixel_src = (QRgb*)src.scanLine(y);
            QRgb *pixel_dst = (QRgb*)dst.scanLine(ys);


            uchar r = qRed(pixel_src[x]);
            uchar g = qGreen(pixel_src[x]);
            uchar b = qBlue(pixel_src[x]);

            pixel_dst[xs] = qRgb(r,g,b);
        }
    }


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
}

void MainWindow::on_actionOpen_triggered()
{
    openImage();
}


void MainWindow::on_horizontalSlider_valueChanged(int value)
{
    rotateImage(originalImage,processImage,value / 100.0f);
    ui->image->setPixmap(QPixmap::fromImage(processImage));
}


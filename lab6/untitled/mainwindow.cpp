#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFileDialog>

void scaleImage(const QImage& src, QImage& dst,float s){
    int w = src.width() * s;
    int h = src.height() * s;
    dst = QImage(w,h,src.format());
//    dst.fill(0) - wyzerowanie obrazka

    for(y = 0; y < src.height(); y++){
        for(x = 0; x < src.width(); x++){
            int xp = round(x / s);
            int yp = round(y / s);
            dst[xp,yp] = src[x,y];

        }
    }
}
// scalowanie w pseudokadzie


void rotateImage(const QImage& src, QImage& dst,float a){
    int w = src.width() * s;
    int h = src.height() * s;
    dst = QImage(w,h,src.format());
    dst.fill(0);

    for(y = 0; y < src.height(); y++){
        for(x = 0; x < src.width(); x++){
            float xp = x*cos(a) - y* sin(a);
            float yp = x*sin(a) + y* cos(a);

            // libo

            int xp = x*cos(-a) + y* sin(-a);
            int yp = x*sin(-a) + y* cos(-a);

            // jest to samo bo sin x jest funkcja nieparzysta cos jest parzysta


            int xd = round(xs);
            int yd = round(ys);
            dst[xp,yp] = src[x,y];

        }
    }
}



void afineImage(const QImage& src, QImage& dst,float* matrix /* float matrix[9]*/){
    int w = src.width() * s;
    int h = src.height() * s;
    dst = QImage(w,h,src.format());
    dst.fill(0);

    for(y = 0; y < src.height(); y++){
        for(x = 0; x < src.width(); x++){

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

}

void MainWindow::on_Open_triggered()
{
    openImage();
}

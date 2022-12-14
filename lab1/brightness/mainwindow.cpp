#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <iostream>
#include <QFileDialog>

void brightness_gamma(const QImage &src, QImage &dst, float gamma) {
    for (int y = 0; y < src.height(); y++) {
        QRgb *pixel_src = (QRgb*)src.scanLine(y);
        QRgb *pixel_dst = (QRgb*)dst.scanLine(y);

        for (int x = 0; x < src.width(); x++) {
            float r = qRed(pixel_src[x]);
            float g = qGreen(pixel_src[x]);
            float b = qBlue(pixel_src[x]);

            r = 255 * pow(r / 255.0f, gamma);
            g = 255 * pow(g / 255.0f, gamma);
            b = 255 * pow(b / 255.0f, gamma);

            pixel_dst[x] = qRgb(r, g, b);
        }
    }
}

void brightness(const QImage &src, QImage &dst, int v) {
    for (int y = 0; y < src.height(); y++) {
        QRgb *pixel_src = (QRgb*)src.scanLine(y);
        QRgb *pixel_dst = (QRgb*)dst.scanLine(y);

        for (int x = 0; x < src.width(); x++) {
            unsigned char r = qRed(pixel_src[x]);
            unsigned char g = qGreen(pixel_src[x]);
            unsigned char b = qBlue(pixel_src[x]);

            r = clamp<int>(r + v, 0, 255);
            g = clamp<int>(g + v, 0, 255);
            b = clamp<int>(b + v, 0, 255);

            pixel_dst[x] = qRgb(r, g, b);
        }
    }
}


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->label->setText("No Image");
}

MainWindow::~MainWindow()
{
    delete ui;
}





#include<QMouseEvent>
void MainWindow::mousePressEvent(QMouseEvent *e){
    if(e->button() == Qt::LeftButton){
        QPoint p = e->pos();
        std::cout << p.x() << " " << p.y() << "\n";
        QPoint label_pos = ui->label->pos();
        label_pos.y();
    }
    else if(e->button()== Qt::RightButton){

    }
}

#include<QKeyEvent>
void MainWindow::keyPressEvent(QKeyEvent *e){
    if(e->key() == Qt::Key_P){

    }
}

void MainWindow::openImage() {
    QString fileName = QFileDialog::getOpenFileName();

    if (!fileName.isNull()) {
        originalImage.load(fileName);
        processImage = originalImage;
        ui->label->setPixmap(QPixmap::fromImage(processImage));
    }
}




void MainWindow::on_actionOpen_triggered()
{
    openImage();
}


void MainWindow::on_horizontalSlider_valueChanged(int v)
{
    brightness(originalImage, processImage, v);
    ui->label->setPixmap(QPixmap::fromImage(processImage));
}


void MainWindow::on_horizontalSlider_2_valueChanged(int v)
{
    float gamma = 0.0f;

    v *= -1;

    if (v <= 0) {
        gamma = (100 + v) / 100.0;
    } else {
        gamma = v / 10.0 + 1;
    }

    brightness_gamma(originalImage, processImage, gamma);
    ui->label->setPixmap(QPixmap::fromImage(processImage));
}


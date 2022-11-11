#include "mainwindow.h"
#include "ui_mainwindow.h"
#include<QMouseEvent>
#include<iostream>
#include <QFileDialog>

void set_pixel_black(int x , int y, QImage &I){
    QRgb *pixel_src = (QRgb*)I.scanLine(y);
    pixel_src[x] = qRgb(0,0,0);
}



void setWhite(QImage &I){
    for (int y = 0; y < I.height(); y++) {
        QRgb *pixel_src = (QRgb*)I.scanLine(y);

        for (int x = 0; x < I.width(); x++) {

            pixel_src[x] = qRgb(255, 255, 255);
        }
    }
}

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QImage white_field = QImage (ui->label->width(),ui->label->height(), QImage::Format_RGB32);
    setWhite(white_field);
    processImage = white_field;
    ui->label->setPixmap(QPixmap::fromImage(processImage));
}

MainWindow::~MainWindow()
{
    delete ui;
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


void MainWindow::mousePressEvent(QMouseEvent *e){
    if(e->button() == Qt::LeftButton){
        QPoint p = e->pos();
        std::cout << p.x() << " " << p.y() << "\n";
        QPoint label_pos = ui->label->pos();
        label_pos.y();
        set_pixel_black(p.x(),p.y(),processImage);
        ui->label->setPixmap(QPixmap::fromImage(processImage));
    }
}


#include "mainwindow.h"
#include "ui_mainwindow.h"
#include<QMouseEvent>
#include<iostream>
#include <QFileDialog>


int click = 0;
int x00, x11, y00, y11;


void change_x_y(int *x0, int* y0, int *x1, int* y1){
    if(x0 > x1){
        int tmp = *x0;
        x0 = x1;
        *x1 = tmp;
    }
    if(y0 > y1){
        int tmp = *y0;
        y0 = y1;
        *y1 = tmp;
    }
}



void set_pixel_black(int x , int y, QImage &I){
    QRgb *pixel_src = (QRgb*)I.scanLine(y);
    pixel_src[x] = qRgb(0,0,0);
}


void draw_line(int x0, int x1, int y0, int y1, QImage &I){
    int d, dx, dy, ai, bi, xi, yi;
    int x = x0, y = y0;


    if (x0 < x1){
        xi = 1;
        dx = x1 - x0;
    }
    else{
        xi = -1;
        dx = x0 - x1;
    }

    if (y0 < y1){
        yi = 1;
        dy = y1 - y0;
    }
    else{
        yi = -1;
        dy = y0 - y1;
    }

    set_pixel_black(x, y, I);


    if (dx > dy){
        ai = (dy - dx) * 2;
        bi = dy * 2;
        d = bi - dx;
        while (x != x1){
            if (d >= 0){
                x += xi;
                y += yi;
                d += ai;
            }
            else{
                d += bi;
                x += xi;
            }
            set_pixel_black(x, y, I);
        }
    }
    else{
        ai = ( dx - dy ) * 2;
        bi = dx * 2;
        d = bi - dy;
        while (y != y1){
            if (d >= 0){
                x += xi;
                y += yi;
                d += ai;
            }
            else{
                d += bi;
                y += yi;
            }
            set_pixel_black(x, y, I);
        }
    }
}


void draw_line_on_second_click(int x, int y, QImage &I){
    std::cout << click << std::endl;
    if(click % 2 == 1){
        x11 = x;
        y11 = y;
        click++;
        draw_line(x00,x11,y00,y11,I);
    }
    else{
        x00 = x;
        y00 = y;
        click++;
    }
}

void setWhite(QImage &I){
    for (int y = 0; y < I.height(); y++) {
        QRgb *pixel_src = (QRgb*)I.scanLine(y);

        for (int x = 0; x < I.width(); x++) {

            pixel_src[x] = qRgb(255, 255, 255);
        }
    }
}

void lines(int x, int y, QImage &I){
    int x000 = 700;
    int y000 = 300;
    draw_line(x000,x000-x,y000,y000-y,I);
    draw_line(x000,x000-x,y000,y000+y,I);
    draw_line(x000,x000+x,y000,y000-y,I);
    draw_line(x000,x000+x,y000,y000+y,I);
    draw_line(x000,x000-y,y000,y000-x,I);
    draw_line(x000,x000-y,y000,y000+x,I);
    draw_line(x000,x000+y,y000,y000-x,I);
    draw_line(x000,x000+y,y000,y000+x,I);
}


void draw_circle_with_lines(int r, QImage &I){
    float d = 5.0-4*r;
    float x = 0;
    float y = r;
    float deltaA = (-2*r+5)*4;
    float deltaB = 3*4;
    while (x <= y) {
        lines(int(x),int(y),I);
        if (d > 0) {
            d += deltaA;
            y -= 1;
            x += 1;
            deltaA += 4*4;
            deltaB += 2*4;
        }
        else {
            d += deltaB;
            x += 1;
            deltaA += 2*4;
            deltaB += 2*4;
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
    draw_circle_with_lines(140,processImage);
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
        draw_line_on_second_click(p.x(),p.y(),processImage);
        ui->label->setPixmap(QPixmap::fromImage(processImage));
    }
}


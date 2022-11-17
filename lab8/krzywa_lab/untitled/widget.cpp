#include "widget.h"
#include <QPainter>
#include <QMouseEvent>
#include <iostream>

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






void drawBezierSegment(QImage& img, std::vector<ivec2>& control_pints)
{

    for(int i = 0; i < 4; i++){
        std::cout << control_pints[i].x << ":" << control_pints[i].y << std::endl;

    }


    float t = 0.0f;
    float step = 1.0 / 8.0; //  16 - ile bedzie ponktow

    int x0 = control_pints[0].x;
    int y0 = control_pints[0].y;
    int cx = 3 * (control_pints[1].x - x0);
    int bx = 3 * (control_pints[2].x - control_pints[1].x) - cx;
    int ax = control_pints[3].x - x0 - cx - bx;
    int cy = 3 * (control_pints[1].y - y0);
    int by = 3 * (control_pints[2].y - control_pints[1].y) - cy;
    int ay = control_pints[3].y - y0 - cy - by;


    int x_s, y_s;

    if(control_pints.size() == 0){
        x_s = ax * t * t * t + bx * t * t + cx * t + x0;
        y_s = ay * t * t * t + by * t * t + cy * t + y0;
        t += step;
    }
    else{
        x_s = control_pints[0].x;
        y_s = control_pints[0].y;
        t += step;
    }

    for(;t <= 1.0;t += step){
        int x = ax * t * t * t + bx * t * t + cx * t + x0;
        int y = ay * t * t * t + by * t * t + cy * t + y0;;
        img.setPixel(x,y,0xff0000);

        draw_line(x_s,x,y_s,y,img);
        x_s = x;
        y_s = y;

    }

     control_pints.clear();
     control_pints.push_back({x_s, y_s});

    // zapomientujemy przeszly x i y
}



Widget::Widget(QWidget *parent)
    : QWidget(parent)
{
    image = QImage(800,800, QImage::Format_RGB32); // argb32
//    image.fill(0xrrggbb);
    image.fill(0xffffff);



}

Widget::~Widget()
{


}

void Widget::mousePressEvent(QMouseEvent * e)
{
    ivec2 p = {e->pos().x(), e->pos().y()};
    control_points.push_back(p);

    if(control_points.size() == 4){
        drawBezierSegment(image, control_points);
        update();
    }


}

void Widget::paintEvent(QPaintEvent *)
{
    QPainter paint(this);
    paint.drawImage(0,0,image);

}





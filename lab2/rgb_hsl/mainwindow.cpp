#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <iostream>

float tC(float x){
    if(x < 0){
        return x + 1;
    }
    else if(x > 1){
        return x - 1;
    }
}



unsigned char tCChar(float x, float p, float q){
    if (x < 0.16666666f){
        return (p + (q - p) * 6 * x) * 255;
    }
    else if(x >= 0.16666666f && x < 0.5f){
        return q * 255;
    }

    else if(x >= 0.5f && x < 0.6666666666f){
        return (p + (q - p) * 6 * (0.6666666666f - x)) * 255;
    }
    else{
        return p * 255;
    }
}

void rgbToHsl(unsigned char r, unsigned char g, unsigned char b, float *h, float *s, float *l){
    float fr = r/255.0f;
    float fg = g/255.0f;
    float fb = b/255.0f;

    float MIN = std::min(fr,std::min(fg,fb));
    float MAX = std::max(fr,std::max(fg,fb));
    float dM = MAX - MIN;

    *l = (MIN + MAX) / 2;

    if(MIN == MAX || l == 0){
        *s = 0;
    }
    else if(*l > 0 && *l < 0.5f){
        *s = dM/(*l * 2);
    }
    else if(*l > 0.5f){
        *s = dM / (2 - 2 * (*l));
    }



    if(MIN == MAX){
        *h = 0;
    }
    else if(MAX == fr && fg >= fb){
        *h = 60 * ((fg-fb)/dM);
    }

    else if(MAX == fr && fg < fb){
        *h = 60 * ((fg-fb)/dM) + 360;
    }

    else if(MAX == fg){
        *h = 60 * ((fb-fr)/dM) + 120;
    }

    else if(MAX == fb){
        *h = 60 * ((fr-fg)/dM) + 240;
    }
}

void hslToRgb(float h, float s, float l,unsigned char *r, unsigned char *g, unsigned char *b){
    if (s == 0){
       *r = l;
       *g = l;
       *b = l;
    }

    float q;
    if(l < 0.5f){
        q = l * (1+s);
    }
    else{
        q = l + s - (l * s);
    }

    float p = 2 * l - q;
    h = h/360;
    float tR = h + 0.33333333333f;
    float tG = h;
    float tB = h - 0.33333333333f;



    tR = tC(tR);
    tG = tC(tG);
    tB = tC(tB);

    *r = tCChar(tR,p,q);
    *g = tCChar(tG,p,q);
    *b = tCChar(tB,p,q);

}



MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);


    float h = 0.5;
    float s = 0.64;
    float l = 0.43;
    unsigned char r = 223;
    unsigned char g = 121;
    unsigned char b = 132;
    rgbToHsl(r,g,b,&h,&s,&l);
    std::cout << h << " " << s  << " "  << l << std::endl;
    hslToRgb(h,s,l,&r,&g,&b);
    std::cout << +r << " " << +g  << " "  << +b << std::endl;

}
MainWindow::~MainWindow()
{
    delete ui;
}


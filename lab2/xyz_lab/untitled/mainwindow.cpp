#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFileDialog>

void rgbToXyz(unsigned char r,unsigned char g,unsigned char b,float* x,float* y,float* z){

    float fr = r / 255.0f;
    float fg = g / 255.0f;
    float fb = b / 255.0f;

    *x = fr * 0.57667f + fg * 0.18556f + fb * 0.18823f;
    *y = fr * 0.29734f + fg * 0.62736f + fb * 0.07529f;
    *z = fr * 0.02703f + fg * 0.07069f + fb * 0.99134f;

}

void xyzToRgb(float x, float y, float z, unsigned char* r, unsigned char* g, unsigned char* b){

    float fr = x * 2.04159f + y * (-0.056501f) + z * (-0.34473f);
    float fg = x * (-0.96924f) + y * (1.87597f) + z * (0.04156f);
    float fb = x * 0.01344f + y * (-0.011836f) + z * (1.01517f);

    *r = uchar(255 * fr);
    *g = uchar(255 * fg);
    *b = uchar(255 * fb);

}

void xyzToLab(float x,float y,float z,float* l,float* a,float* b){
    float xr = x / 0.9505f;
    float yr = y / 1.0f;
    float zr = z / 1.0891f;

    float fx,fy,fz;
    float k = 903.3f;
    float e = 0.008856f;

    if(xr > e){
        fx = std::pow(xr,0.33333);
    }
    else{
        fx = (k*xr + 16) / 116.f;
    }

    if(yr > e){
        fy = std::pow(yr,0.33333);
    }
    else{
        fz = (k*yr + 16) / 116.f;
    }

    if(zr > e){
        fz = std::pow(xr,0.33333);
    }
    else{
        fz = (k*zr + 16) / 116.f;
    }

    *l = 116 * fy - 16;
    *a = 500 * (fx - fy);
    *b = 200 * (fy - fz);

}

void labToXyz(float l,float a,float b,float* x,float* y,float* z){

    float k = 903.3f;
    float e = 0.008856f;
    float xr,yr,zr,fx,fy,fz;

    if(l > k * e){
        yr = std::pow((l+16) / 116.0f,3);
    }
    else{
        yr = l / k;
    }

    if(yr > e){
        fy = (l +16) / 116.0f;
    }
    else{
        fy = (k * yr + 16) / 116.0f;
    }


    fx = (a/500.0f) + fy;
    fz = fy - (b/200.0f);

    if (std::pow(fx,3) > e){
        xr = std::pow(fx,3);
    }
    else{
        xr = (116*fx - 16)/ k;
    }

    if (std::pow(fz,3) > e){
        zr = std::pow(fz,3);
    }
    else{
        zr = (116*fz - 16)/ k;
    }


    *x = xr * 0.9505f;
    *y = yr * 1.0f;
    *z = zr * 1.0891f;

}

void lab_modify(const QImage &src, QImage &dst, float ll, float aa, float bb){
    for(int y = 0; y < src.height(); y++){


        QRgb *pixel_src = (QRgb*)src.scanLine(y);
        QRgb *pixel_dst = (QRgb*)dst.scanLine(y);

        for(int x = 0; x < src.width(); x++){
            unsigned char r = qRed(pixel_src[x]);
            unsigned char g = qGreen(pixel_src[x]);
            unsigned char b = qBlue(pixel_src[x]);


            float xx= 0.0f,yy= 0.0f,zz= 0.0f;
            float fl= 0.0f,fa= 0.0f,fb= 0.0f;

            rgbToXyz(r,g,b,&xx,&yy,&zz);
            xyzToLab(xx,yy,zz,&fl,&fa,&fb);

            float tl = clamp<float>(ll + fl, 0, 100);
            float ta = clamp<float>(aa + fa, -128, 127);
            float tb = clamp<float>(bb + fb, -128, 127);

            labToXyz(tl,ta,tb,&xx,&yy,&zz);
            xyzToRgb(xx,yy,zz,&r,&g,&b);

            pixel_dst[x] = qRgb(r,g,b);
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
        ui->image->setPixmap(QPixmap::fromImage(processImage));
    }
}


void MainWindow::on_actionOpen_triggered()
{
    openImage();
}


void MainWindow::on_aSlider_valueChanged(int action)
{
    lab_modify(originalImage, processImage,ui->lSlider->value(),action,ui->bSlider->value());
    ui->image->setPixmap(QPixmap::fromImage(processImage));
}


void MainWindow::on_bSlider_valueChanged(int action)
{
    lab_modify(originalImage, processImage,ui->lSlider->value(),ui->aSlider->value(),action);
    ui->image->setPixmap(QPixmap::fromImage(processImage));
}

void MainWindow::on_lSlider_valueChanged(int action)
{
    lab_modify(originalImage, processImage,action,ui->aSlider->value(),ui->bSlider->value());
    ui->image->setPixmap(QPixmap::fromImage(processImage));
}


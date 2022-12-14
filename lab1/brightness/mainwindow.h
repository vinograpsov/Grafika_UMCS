#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QImage>
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

template<class T>
T clamp(T v, T minv, T maxv) {
    if (v >= maxv) return maxv;
    if (v <= minv) return minv;
    return v;
}
class MainWindow : public QMainWindow
{
    Q_OBJECT
    QImage originalImage;
    QImage processImage;

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();



// eventy kliknincia
protected:
    void mousePressEvent(QMouseEvent*); // kliknincie
//    void mouseReleaseEvent(QMouseEvent*); // kiedy puscimy
//    void mouseDoubleClickEvent(QMouseEvent*);
//    void mouseMoveEvent(QMouseEvent*);

    void keyPressEvent(QKeyEvent*);
//    void keyReleaseEvent(QKeyEvent*);





public slots:
    void openImage();

private slots:
    void on_actionOpen_triggered();
    void on_horizontalSlider_valueChanged(int value);
    void on_horizontalSlider_2_valueChanged(int value);

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT
    QImage originalImage;
    QImage processImage;

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

public slots:
    void openImage();


private slots:
    void on_actionOpen_triggered();

    void on_hSlider_actionTriggered(int action);

    void on_lSlider_actionTriggered(int action);

    void on_sSlider_actionTriggered(int action);

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H

/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.4.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QSlider>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *actionOpen;
    QWidget *centralwidget;
    QWidget *verticalLayoutWidget;
    QVBoxLayout *verticalLayout;
    QSlider *hSlider;
    QSlider *sSlider;
    QSlider *lSlider;
    QLabel *image;
    QMenuBar *menubar;
    QMenu *menufile;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(800, 600);
        actionOpen = new QAction(MainWindow);
        actionOpen->setObjectName("actionOpen");
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        verticalLayoutWidget = new QWidget(centralwidget);
        verticalLayoutWidget->setObjectName("verticalLayoutWidget");
        verticalLayoutWidget->setGeometry(QRect(9, 9, 771, 531));
        verticalLayout = new QVBoxLayout(verticalLayoutWidget);
        verticalLayout->setObjectName("verticalLayout");
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        hSlider = new QSlider(verticalLayoutWidget);
        hSlider->setObjectName("hSlider");
        hSlider->setMinimum(-180);
        hSlider->setMaximum(180);
        hSlider->setOrientation(Qt::Horizontal);

        verticalLayout->addWidget(hSlider);

        sSlider = new QSlider(verticalLayoutWidget);
        sSlider->setObjectName("sSlider");
        sSlider->setMinimum(-100);
        sSlider->setMaximum(100);
        sSlider->setOrientation(Qt::Horizontal);

        verticalLayout->addWidget(sSlider);

        lSlider = new QSlider(verticalLayoutWidget);
        lSlider->setObjectName("lSlider");
        lSlider->setMinimum(-100);
        lSlider->setMaximum(100);
        lSlider->setOrientation(Qt::Horizontal);

        verticalLayout->addWidget(lSlider);

        image = new QLabel(verticalLayoutWidget);
        image->setObjectName("image");

        verticalLayout->addWidget(image);

        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 800, 22));
        menufile = new QMenu(menubar);
        menufile->setObjectName("menufile");
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName("statusbar");
        MainWindow->setStatusBar(statusbar);

        menubar->addAction(menufile->menuAction());
        menufile->addAction(actionOpen);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        actionOpen->setText(QCoreApplication::translate("MainWindow", "Open", nullptr));
        image->setText(QCoreApplication::translate("MainWindow", "TextLabel", nullptr));
        menufile->setTitle(QCoreApplication::translate("MainWindow", "file", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H

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
    QVBoxLayout *histogramsLayout;
    QLabel *histGreen;
    QLabel *histBlue;
    QLabel *histRed;
    QWidget *verticalLayoutWidget_2;
    QVBoxLayout *pictureLayout;
    QLabel *image;
    QMenuBar *menubar;
    QMenu *menuFile;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(1199, 714);
        actionOpen = new QAction(MainWindow);
        actionOpen->setObjectName("actionOpen");
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        verticalLayoutWidget = new QWidget(centralwidget);
        verticalLayoutWidget->setObjectName("verticalLayoutWidget");
        verticalLayoutWidget->setGeometry(QRect(690, 10, 491, 651));
        histogramsLayout = new QVBoxLayout(verticalLayoutWidget);
        histogramsLayout->setObjectName("histogramsLayout");
        histogramsLayout->setContentsMargins(0, 0, 0, 0);
        histGreen = new QLabel(verticalLayoutWidget);
        histGreen->setObjectName("histGreen");

        histogramsLayout->addWidget(histGreen);

        histBlue = new QLabel(verticalLayoutWidget);
        histBlue->setObjectName("histBlue");

        histogramsLayout->addWidget(histBlue);

        histRed = new QLabel(verticalLayoutWidget);
        histRed->setObjectName("histRed");

        histogramsLayout->addWidget(histRed);

        verticalLayoutWidget_2 = new QWidget(centralwidget);
        verticalLayoutWidget_2->setObjectName("verticalLayoutWidget_2");
        verticalLayoutWidget_2->setGeometry(QRect(19, 9, 661, 651));
        pictureLayout = new QVBoxLayout(verticalLayoutWidget_2);
        pictureLayout->setObjectName("pictureLayout");
        pictureLayout->setContentsMargins(0, 0, 0, 0);
        image = new QLabel(verticalLayoutWidget_2);
        image->setObjectName("image");

        pictureLayout->addWidget(image);

        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 1199, 22));
        menuFile = new QMenu(menubar);
        menuFile->setObjectName("menuFile");
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName("statusbar");
        MainWindow->setStatusBar(statusbar);

        menubar->addAction(menuFile->menuAction());
        menuFile->addAction(actionOpen);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        actionOpen->setText(QCoreApplication::translate("MainWindow", "Open", nullptr));
        histGreen->setText(QCoreApplication::translate("MainWindow", "TextLabel", nullptr));
        histBlue->setText(QCoreApplication::translate("MainWindow", "TextLabel", nullptr));
        histRed->setText(QCoreApplication::translate("MainWindow", "TextLabel", nullptr));
        image->setText(QCoreApplication::translate("MainWindow", "TextLabel", nullptr));
        menuFile->setTitle(QCoreApplication::translate("MainWindow", "File", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H

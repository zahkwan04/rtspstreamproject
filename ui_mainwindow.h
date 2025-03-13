/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.14.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QVBoxLayout *verticalLayout;
    QPushButton *selectFileButton;
    QLabel *filePathLabel;
    QPushButton *startStreamButton;
    QPushButton *stopStreamButton;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(400, 250);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        verticalLayout = new QVBoxLayout(centralwidget);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        selectFileButton = new QPushButton(centralwidget);
        selectFileButton->setObjectName(QString::fromUtf8("selectFileButton"));

        verticalLayout->addWidget(selectFileButton);

        filePathLabel = new QLabel(centralwidget);
        filePathLabel->setObjectName(QString::fromUtf8("filePathLabel"));

        verticalLayout->addWidget(filePathLabel);

        startStreamButton = new QPushButton(centralwidget);
        startStreamButton->setObjectName(QString::fromUtf8("startStreamButton"));

        verticalLayout->addWidget(startStreamButton);

        stopStreamButton = new QPushButton(centralwidget);
        stopStreamButton->setObjectName(QString::fromUtf8("stopStreamButton"));

        verticalLayout->addWidget(stopStreamButton);

        MainWindow->setCentralWidget(centralwidget);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        selectFileButton->setText(QCoreApplication::translate("MainWindow", "Select Video File", nullptr));
        filePathLabel->setText(QCoreApplication::translate("MainWindow", "No file selected", nullptr));
        startStreamButton->setText(QCoreApplication::translate("MainWindow", "Start Streaming", nullptr));
        stopStreamButton->setText(QCoreApplication::translate("MainWindow", "Stop Streaming", nullptr));
        (void)MainWindow;
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H

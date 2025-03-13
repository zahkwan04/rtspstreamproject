#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "rtspstreamer.h"
#include <QFileDialog>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_selectFileButton_clicked();
    void on_startStreamButton_clicked();
    void on_stopStreamButton_clicked();

private:
    Ui::MainWindow *ui;
    RtspStreamer *streamer;
    QString videoFilePath;
};

#endif // MAINWINDOW_H

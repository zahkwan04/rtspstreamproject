#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow), streamer(new RtspStreamer) {
    ui->setupUi(this);
}

MainWindow::~MainWindow() {
    delete ui;
    delete streamer;
}

void MainWindow::on_selectFileButton_clicked() {
    videoFilePath = QFileDialog::getOpenFileName(this, "Select Video File", "", "Videos (*.mp4 *.avi *.mkv)");
    if (!videoFilePath.isEmpty()) {
        ui->filePathLabel->setText(videoFilePath);
    }
}

void MainWindow::on_startStreamButton_clicked() {
    if (!videoFilePath.isEmpty()) {
        streamer->startStreaming(videoFilePath);
    }
}

void MainWindow::on_stopStreamButton_clicked() {
    streamer->stopStreaming();
}

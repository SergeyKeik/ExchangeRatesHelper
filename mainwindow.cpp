#include "mainwindow.h"


MainWindow::MainWindow(QWidget *parent):
    QWidget(parent)
{
    widget_ = new QWidget(this);
    layout_ = new QVBoxLayout(this);
    buttonSt_ = new QPushButton("Начать загрузку", this);
    buttonFin_ = new QPushButton("Остановить загрузку", this);
    quit_ = new QPushButton("Выход", this);
    labelCur_ = new QLabel(this);
    labelCur_->resize(1000, 700);
    labelMid_ = new QLabel(this);
    getFileFromServer_ = new Downloader();
    layout_->setSizeConstraint(QLayout::SetMinimumSize);
    timer_ = new QTimer(this);
    connect(buttonSt_, &QPushButton::clicked, this, &MainWindow::startDownload);

    //connect(buttonSt, &QPushButton::clicked, getFileFromServer, &Downloader::getData);
    connect(quit_, &QPushButton::clicked, qApp, &QApplication::quit);
    connect(buttonFin_, &QPushButton::clicked, this, &MainWindow::stopDownload);
    connect(timer_, &QTimer::timeout, this, &MainWindow::showCur);
    layout_->addWidget(buttonSt_);
    layout_->addWidget(buttonFin_);
    layout_->addWidget(quit_);
    layout_->addWidget(labelCur_);
    layout_->addWidget(labelMid_);
    widget_->setLayout(layout_);
}

void MainWindow::showCur(){
    labelCur_->setText("<b>Текущее значение: <\b>");
    getFileFromServer_->getData();
    labelMid_->setText(getFileFromServer_->getString());
}

void MainWindow::startDownload() {
    showCur();
    timer_->start(10000);
}

void MainWindow::stopDownload() {
    timer_->stop();
    labelCur_->setText("<b>Среднее и медианное значения: <\b>");
    labelMid_->setText(getFileFromServer_->getAverageString());
    getFileFromServer_->clearHistory();
}

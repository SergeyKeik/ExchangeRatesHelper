#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QObject>
#include <QWidget>
#include <QApplication>
#include <QVBoxLayout>
#include <QString>
#include <QLabel>
#include <QPushButton>
#include <downloader.h>
#include <QTimer>

class MainWindow : public QWidget
{
    Q_OBJECT;
public:
    MainWindow(QWidget *parent = nullptr);

public slots:
    void showCur();
    void startDownload();
    void stopDownload();
private:
    QPushButton *buttonSt_;
    QPushButton *buttonFin_;
    QPushButton *quit_;
    QLabel *labelCur_;
    QLabel *labelMid_;
    QWidget *widget_;
    QVBoxLayout *layout_;
    QString text_;
    Downloader *getFileFromServer_;
    QTimer *timer_;
};

#endif // MAINWINDOW_H

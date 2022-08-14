#ifndef DOWNLOADER_H
#define DOWNLOADER_H

#include <QObject>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QNetworkRequest>
#include <QFile>
#include <QUrl>
#include <QDebug>
#include <QEventLoop>
#include <jsonparsing.h>


class Downloader : public QObject
{
    Q_OBJECT
public:
    explicit Downloader(QObject *parent = nullptr);
    QString& getString() {
        return data_;
    }
    QString& getAverageString();
    ~Downloader() {
        delete jsFile_;
    }
    void clearHistory() {
        dataVec_.clear();
        averageString_ = "";
        firstFile_ = true;
    }

public slots:
    void getData();
    void processRes(QNetworkReply *reply);
    void beginProcessRes();

signals:
    void processingComplete();
private:
    QNetworkAccessManager *manager_;
    QEventLoop loop_;
    JFile *jsFile_;
    QString data_;
    QString averageString_;
    std::vector<Currency> dataVec_;
    bool firstFile_;
};

#endif // DOWNLOADER_H

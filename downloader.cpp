#include "downloader.h"


Downloader::Downloader(QObject *parent)
    : QObject{parent}
{
    manager_ = new QNetworkAccessManager();
    connect(manager_, &QNetworkAccessManager::finished, this, &Downloader::processRes);
    connect(manager_, &QNetworkAccessManager::finished, &loop_, &QEventLoop::quit);
    firstFile_ = true;
}

QString& Downloader::getAverageString() {
    for (int i = 0; i < 34; ++i) {
    averageString_ += QString::number(dataVec_[i].getNominal()) + " " +
            dataVec_[i].getName() + ": 1) среднее: " + QString::number(dataVec_[i].getAverage()) +
            " 2) медианное: " + QString::number(dataVec_[i].getMedian()) + "\n";
    }
    return averageString_;
}

void Downloader::getData() {
    QUrl url("https://www.cbr-xml-daily.ru/daily_json.js");
    QNetworkRequest request;
    request.setUrl(url);
    manager_->get(request);
    beginProcessRes();
}

void Downloader::processRes(QNetworkReply *reply) {
    if (reply->error()) {
            qDebug() << "Could not get the reply from server\n";
            qDebug() << reply->errorString();
} else {
        QFile *file = new QFile("D:/Programming/Sem2/Lab2/Lab2/file.js");
        if (file->open(QFile::WriteOnly)) {
            file->write(reply->readAll());
            file->close();
        }
        qDebug() << "Succesful request\n";
        QFile js;
        js.setFileName("D:/Programming/Sem2/Lab2/Lab2/file.js");
        js.open(QIODevice::ReadOnly | QIODevice::Text);

        QJsonDocument json = QJsonDocument::fromJson(js.readAll());

        QJsonObject obj = json.object();
        jsFile_ = new JFile(obj);
        data_ = "";
        QJsonObject currencies = jsFile_->getCurrencies();
        QJsonObject::Iterator it;
        int i = 0;
        for(it = currencies.begin(); it != currencies.end(); ++it) {
            Currency curValue{it->toObject()};
            data_ += (curValue.getCurrencyStr());
            if (firstFile_) {
                dataVec_.push_back(curValue);
            }
            dataVec_[i].addAverageAndHist(curValue.getValue());
            ++i;
        }
        firstFile_ = false;

        delete jsFile_;
        emit processingComplete();
    }
}

void Downloader::beginProcessRes() {
    loop_.exec();
}

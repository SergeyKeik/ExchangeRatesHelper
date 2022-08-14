#ifndef JSONPARSING_H
#define JSONPARSING_H

#include <QJsonDocument>
#include <QJsonValue>
#include <QJsonArray>
#include <QJsonObject>
#include <vector>
#include <iostream>
#include <algorithm>
#include <QString>


class Currency {
public:
    Currency(QJsonObject curObject);
    QString getCurrencyStr();
    void addAverageAndHist(double newValue) {
        sumOfValues_ += newValue;
        history_.push_back(newValue);
        ++numOfRequests_;
    }
    double getValue() {
        return value_;
    }
    const QString& getName() {
        return name_;
    }
    int getNominal() {
        return nominal_;
    }
    double getAverage() {
        return sumOfValues_ / numOfRequests_;
    }
    double getMedian() {
        std::size_t index = history_.size() / 2;
        std::nth_element(history_.begin(), history_.begin() + index, history_.end());
        if (history_.size() % 2 == 1) {
            return history_[index];
        } else {
            std::nth_element(history_.begin(), history_.end() + (index - 1), history_.end());
            return (history_[index] + history_[index - 1]) / 2;
        }
    }
private:
    QString  id_;
    QString numCode_;
    QString charCode_;
    int nominal_;
    QString name_;
    double value_;
    double prevValue_;
    double sumOfValues_;
    int numOfRequests_;
    std::vector<double> history_;

};

class JFile{
public:
    JFile (QJsonObject fileObject);
    QJsonObject getCurrencies() {
        return currencies_;
    }
private:
    QString date_;
    QString prevDate_;
    QString prevURL_;
    QString timestamp_;
    QJsonObject currencies_;
};

#endif // JSONPARSING_H

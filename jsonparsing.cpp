#include "jsonparsing.h"

Currency::Currency(QJsonObject curObject):
    id_{curObject.value("ID").toString()},
    numCode_{curObject.value("NumCode").toString()},
    charCode_{curObject.value("CharCode").toString()},
    nominal_{curObject.value("Nominal").toInt()},
    name_{curObject.value("Name").toString()},
    value_{curObject.value("Value").toDouble()},
    prevValue_{curObject.value("Previous").toDouble()},
    sumOfValues_{0},
    numOfRequests_{0}
{

}
JFile::JFile (QJsonObject fileObject):
    date_{fileObject.value("Date").toString()},
    prevDate_{fileObject.value("PreviousDate").toString()},
    prevURL_{fileObject.value("PreviousURL").toString()},
    timestamp_{fileObject.value("Timestamp").toString()} {

    currencies_ = fileObject.value("Valute").toObject();
}

QString Currency::getCurrencyStr() {
    QString curString;
    curString =  QString::number(nominal_) + " " + name_ + ": " + QString::number(value_) + " рублей.\n";
    return curString;
}

#include "controller.h"
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QUrl>
#include <QUrlQuery>
#include <QtNetwork/QNetworkAccessManager>
#include <QtNetwork/QNetworkReply>
#include <QtNetwork/QNetworkRequest>
#include <QDebug>
#include <QFile>
#include <iostream>
#include <utility>
Controller::Controller(QObject *parent) : QObject(parent), cityList(new QVector<QString>()) , weatherData(new std::pair<QJsonObject, QJsonObject>()) {
    readSavedData();
}

void Controller::getWeatherData(QUrl &url, bool isLt) {

    QNetworkAccessManager *manager = new QNetworkAccessManager(this);
    if(isLt)
        connect(manager, SIGNAL(finished(QNetworkReply*)), this, SLOT(ltReplyFinished(QNetworkReply*)));
    else
        connect(manager, SIGNAL(finished(QNetworkReply*)), this, SLOT(replyFinished(QNetworkReply*)));

    QNetworkRequest request(url);

    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/x-www-form-urlencoded");
    //std::cout<< url.toString().toStdString()<<std::endl;

    manager->post(request, url.toEncoded());

}

void Controller::replyFinished(QNetworkReply *reply) {
    if ( reply->error() != QNetworkReply::NoError ) {
        // A communication error has occurred
        std::cout << "Network Error" << std::endl;
        return;
    }
    weatherData->first = QJsonDocument::fromJson(reply->readAll()).object();
    //std::cout << "in replyFinished" << std::endl;
    int num = weatherData->first["list"].toArray()[0].toObject()["id"].toDouble();
    QString id;
    id.setNum(num);
    QUrl url2("http://api.openweathermap.org/data/2.5/forecast/daily?id=" + id + "&cnt=7" + "&APPID=291cc02999b830ce1d7bf176d3d49172");
    getWeatherData(url2,true);


}

void Controller::ltReplyFinished(QNetworkReply *reply) {
    if ( reply->error() != QNetworkReply::NoError ) {
        // A communication error has occurred
        std::cout << "Network Error" << std::endl;
        return;
    }
    weatherData->second = QJsonDocument::fromJson(reply->readAll()).object();
    emit dataLoaded();

}

void Controller::loadWeather(QString name) {
    QUrl url1("http://api.openweathermap.org/data/2.5/find?q=" + name + "&cnt=1" + "&type=like&APPID=291cc02999b830ce1d7bf176d3d49172");
    getWeatherData(url1,false);
    //std::cout << "in load" << std::endl;

}

void Controller::readSavedData() {
    QFile file("saveddata.sav");
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
        return;

    QTextStream in(&file);
    std::cout << "in read data" << std::endl;

    while (!in.atEnd()) {

        QString line = in.readLine();
        addCity(line);
    }

}

void Controller::saveData() {
    QFile file("saveddata.sav");
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
        return;
    QTextStream out(&file);
    for(QVector< QString >::iterator it = cityList->begin(); it != cityList->end(); ++it)
        out << *it << "\n";


}


QVector<QString> &Controller::getCityList() {
    return *cityList;
}

void Controller::addCity(QString name) {

    cityList->append(name);
}

void Controller::removeCity(int idx) {
    cityList->remove(idx);
}
std::pair<QJsonObject, QJsonObject> &Controller::getWeatherData() {
    return *weatherData;
}

Controller::~Controller() {
    saveData();
}


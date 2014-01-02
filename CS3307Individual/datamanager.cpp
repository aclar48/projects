/*
 *Author: Alex Clarke
 *File: datamanager.cpp
 *Description: An openweather compatiable class to handle network and data loading/storing
 *Date: Oct 4, 2013
 */

#include "datamanager.h"
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

/*
 * Default constructor, loads in any saved data
 */
Datamanager::Datamanager(QObject *parent) : QObject(parent), cityList(new QVector<City>()) , weatherData(new std::pair<QJsonObject, QJsonObject>()) {
    readSavedData();
}

/*
 * Destructor, saves the data then deletes heap allocated members
 */
Datamanager::~Datamanager() {
    saveData();
    delete weatherData;
    delete cityList;
}
/*
 * Read in saved data from disk, do nothing if save file doesn't exist
 */
void Datamanager::readSavedData() {
    QFile file("saveddata.sav");
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))  //Attempt to open the file, return if file cannot be opened
        return;

    QTextStream in(&file);
    while (!in.atEnd()) {
        QString line = in.readLine();
        City *tempCity = new City(line.section(" ",0,0).toInt(), line.section(" ", -1,-1)); //Read in the file separating id and name
        cityList->append(*tempCity);    //Add loaded files to list of cities
    }
}
/*
 * Save the city list to disk
 */
void Datamanager::saveData() {
    QFile file("saveddata.sav");
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) //Open the saved data file, creating it if it doesn't exist
        return;
    QTextStream out(&file);
    for(QVector<City>::iterator it = cityList->begin(); it != cityList->end(); ++it)
        out << it->getId() << " " << it->getName() << "\n"; //Write to file in format 'id' 'name'
}

/*
 * Get the list of cities
 * Return: QVector<City> - the list of saved cities;
 */
QVector<City> &Datamanager::getCityList() {
    return *cityList;
}

/*
 * Get the current and longterm weather data
 * Return: std::pair<QJsonObject,QJsonObject> - the current/long term weather data
 */
std::pair<QJsonObject, QJsonObject> &Datamanager::getWeatherData() {
    return *weatherData;
}

/*
 * Add a city to the city list by id and name
 * Params: int id - the id of the city, QString name - the name of the city
 */
void Datamanager::addCity(const int id, const QString name) {
    City temp(id,name);
    cityList->append(temp);
}

/*
 * Remove a city from the list given its position in the cityList vector
 * Params: int idx - the index of the city to be removed
 */
void Datamanager::removeCity(const int idx) {
    cityList->remove(idx);
}

/*
 * Search for a city given a name
 * Param: QString name - the name of the city to search for
 */
void Datamanager::loadWeatherByName(const QString &name) {
    QUrl url1("http://api.openweathermap.org/data/2.5/find?q=" + name + "&cnt=1" + "&type=like&APPID=291cc02999b830ce1d7bf176d3d49172");
    getWeatherData(url1,false);
}

/*
 * Look up a city by openweathermap city id
 * Param: int id - the id of the city
 */
void Datamanager::loadWeatherById(const int id) {
    QString tempId;
    tempId.setNum(id);
    QUrl url1("http://api.openweathermap.org/data/2.5/weather?id=" + tempId + "&APPID=291cc02999b830ce1d7bf176d3d49172");
    getWeatherData(url1,false);
}

/*
 * loads the weather info from url
 * Params: QUrl &url - the url to query, bool isLt - if the data is for the long term forecase
 */
void Datamanager::getWeatherData(const QUrl &url, const bool isLt) {

    QNetworkAccessManager *manager = new QNetworkAccessManager(this);
    if(isLt)
        connect(manager, SIGNAL(finished(QNetworkReply*)), this, SLOT(ltReplyFinished(QNetworkReply*)));
    else
        connect(manager, SIGNAL(finished(QNetworkReply*)), this, SLOT(replyFinished(QNetworkReply*)));

    QNetworkRequest request(url);

    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/x-www-form-urlencoded");

    manager->post(request, url.toEncoded());

}

/*
 * Private slot to handle the data from a current weather query, then fetch the assoicated long term weather data
 */
void Datamanager::replyFinished(QNetworkReply *reply) {
    if ( reply->error() != QNetworkReply::NoError ) {
        // A communication error has occurred
        std::cout << "Network Error" << std::endl;
        return;
    }
    weatherData->first = QJsonDocument::fromJson(reply->readAll()).object();
    int num = weatherData->first["list"].toArray()[0].toObject()["id"].toDouble();
    if(num == 0) num = weatherData->first["id"].toDouble(); //Check if the data is being loaded from an id query or a search query
    QString id;
    id.setNum(num);
    QUrl url2("http://api.openweathermap.org/data/2.5/forecast/daily?id=" + id + "&cnt=7" + "&APPID=291cc02999b830ce1d7bf176d3d49172");
    getWeatherData(url2,true);
}

/*
 * Private slot to hand the data from a long term weather query
 */
void Datamanager::ltReplyFinished(QNetworkReply *reply) {
    if ( reply->error() != QNetworkReply::NoError ) {
        // A communication error has occurred
        std::cout << "Network Error" << std::endl;
        return;
    }
    weatherData->second = QJsonDocument::fromJson(reply->readAll()).object();
    emit dataLoaded();
}




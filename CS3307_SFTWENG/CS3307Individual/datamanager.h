/*
 *Author: Alex Clarke
 *File: datamanager.h
 *Description: An openweather compatiable class to handle network and data loading/storing
 *Date: Oct 4, 2013
 */

#ifndef DATAMANAGER_H
#define DATAMANAGER_H

#include <utility>
#include <QObject>
#include <QNetworkReply>
#include "city.h"

class Datamanager : public QObject
{
    Q_OBJECT
public:
    explicit Datamanager(QObject *parent = 0);
    ~Datamanager();
    QVector<City> &getCityList();
    std::pair<QJsonObject, QJsonObject> &getWeatherData();
    void addCity(const int id,const QString name);
    void removeCity(const int idx);
    void loadWeatherByName(const QString &name);
    void loadWeatherById(const int id);

signals:
    void dataLoaded();

private:
    QVector<City>  *cityList;     //id,name
    std::pair<QJsonObject, QJsonObject> *weatherData;  //Current/Long Term

    void getWeatherData(const QUrl &url,const bool isLt);
    void readSavedData();
    void saveData();

private slots:
   void replyFinished(QNetworkReply *reply);
   void ltReplyFinished(QNetworkReply *reply);


};

#endif //DATAMANAGER_H

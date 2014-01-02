#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <QObject>
#include <QString>
#include <QtNetwork/QNetworkReply>
#include <QJsonDocument>
#include <QJsonObject>
#include <QUrl>
#include <QVector>
#include <utility>
#include "city.h"

class Controller : public QObject
{
    Q_OBJECT
public:
    explicit Controller(QObject *parent = 0);
    ~Controller();
    void loadWeather(QString name);
    QVector<QString> &getCityList();
    std::pair<QJsonObject, QJsonObject> &getWeatherData();
    void addCity(QString name);
    void removeCity(int idx);

signals:
    void dataLoaded();

private slots:
   void replyFinished(QNetworkReply *reply);
   void ltReplyFinished(QNetworkReply *reply);

private:
    QVector<QString> *cityList;     //id,name
    std::pair<QJsonObject, QJsonObject> *weatherData;  //Current/Long Term


    void getWeatherData(QUrl &url, bool isLt);
    void readSavedData();
    void saveData();


};

#endif // CONTROLLER_H

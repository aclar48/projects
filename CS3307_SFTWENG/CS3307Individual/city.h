/*
 *Author: Alex Clarke
 *File: city.h
 *Description: An openweather compatiable city for storing and loading weather information
 *Date: Oct 4, 2013
 */

#ifndef CITY_H
#define CITY_H

#include <utility>
#include <QObject>
#include <QJsonObject>

class City
{
public:
    City();
    City(const int id,const QString name);
    City(const City &other);
    City& operator= (const City& param);
    ~City();
    bool operator== (const City& param);
    void loadCity(const QJsonObject &curWea,const QJsonObject &ltWea);
    QString getName();
    QString getCurTemp();
    QString getCurMetricTemp();
    QString getCurImperialTemp();
    QString getCurPressure();
    QString getCurImperialPressure();
    QString getCurHumidity();
    QString getCurImg();
    QString getCurCond();
    int getId();
    std::pair<QString,QString> getCurMinMax();
    std::pair<QString,QString> getCurMetricMinMax();
    std::pair<QString,QString> getCurImperialMinMax();
    QVector<QString> &getLtImgs();
    QVector<QString> &getLtConds();
    QVector<QString> &getLtDays();
    QVector<std::pair<QString,QString> > &getLtTemps();
    QVector<std::pair<QString,QString> > &getLtMetricTemps();
    QVector<std::pair<QString,QString> > &getLtImperialTemps();
    

private:

    int id;
    QString name;
    QString curTemp;
    QString curImpTemp;
    QString curMetricTemp;
    QString curPressure;
    QString curImperialPres;
    QString curHumidity;
    QString curImg;
    QString curCond;
    std::pair< QString, QString > curMetricMinMax;            //< MinTemp, MaxTemp>
    std::pair< QString, QString > curImperialMinMax;          //< MinTemp, MaxTemp>
    std::pair< QString, QString > curMinMax;                  //< MinTemp, MaxTemp>
    QVector<QString> *imgs;     //condition image list
    QVector<QString> *conds;    //conditions list
    QVector<QString> *days;     //days list
    QVector<std::pair<QString,QString> > *temps;         //< MinTemp, MaxTemp>
    QVector<std::pair<QString,QString> > *tempsMec;         //< MinTemp, MaxTemp>
    QVector<std::pair<QString,QString> > *tempsImp;         //< MinTemp, MaxTemp>
    
    void loadLongTerm(const QJsonObject &ltWea);
    void generateDays(const QVector<QDateTime> &daylist);


};

#endif // CITY_H

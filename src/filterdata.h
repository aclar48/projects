/**
  @file filterdata.h
  @author Alex Clarke, Jamie Finnigan
  @version 1.0

  @section DESCRIPTION

  Header for the data handler

  */

#ifndef FILTERDATA_H
#define FILTERDATA_H
#include <QObject>
#include <QVector>
#include <QFile>
#include <QObject>
#include <QDebug>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlRecord>
#include "data.h"


class FilterData: public QObject
{
    Q_OBJECT
public:
    FilterData();
    FilterData(const Data &data);
    FilterData(const FilterData &param);
    FilterData& operator= (const FilterData &param);
    virtual ~FilterData();
    static QVector<QString> &loadTemplate(QFile &file);
    static void saveTemplate(const QVector<QString> &prefs, QFile& file);
    void addYear(const QString &skey, const QString &mkey, const QString &mukey, Year &year);
    void addMuni(const QString &skey, const QString &mkey,const Municipality &muni);
    void addMeasure(const QString &skey,const Measure &measure);
    Measure &loadMeasure(const QString &servType,const QString &measure);
    static void saveTable(const QVector<QString> &table, QFile &file);
    const QMap<QString,ServiceType>& serviceList();
    const QMap<QString,QString>& serviceNameList();
    const QString& serviceName(const QString& key);
public slots:
    void parseService(QString);
    void parseMeasures(QString, QString);
signals:
    void measureReady(const QString& sID, const QString& mID, const QString& label);
    void resultReady(Measure& m);
private:
    void loadFromDB();
    bool initDatabase();
    void generateServices();
    Data *_data;
    QSqlDatabase *_db;
    int _numberOfEntries;

};

#endif // FILTERDATA_H

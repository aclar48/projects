/*
 *Author: Alex Clarke
 *File: city.cpp
 *Description: An openweather compatiable city for storing and loading weather information
 *Date: Oct 4, 2013
 */
#include "city.h"
#include <QObject>
#include <QString>
#include <QVector>
#include <QDateTime>
#include <QJsonObject>
#include <QJsonArray>
#include <utility>
#include <iostream>

/*
 *Default Constructor
 */
City::City() :
    imgs(new QVector<QString>()), conds(new QVector<QString>()),
    days(new QVector<QString>()), temps(new QVector<std::pair<QString,QString> >()) ,tempsMec(new QVector<std::pair<QString,QString> >()),
    tempsImp(new QVector<std::pair<QString,QString> >())    {
}
/*
 *Overloaded Constructor, allows the creation of a basic city with just a name and id
 *Params: int id - the id of the city, QString name - the name of the city
 */
City::City(const int id, const QString name) :
    imgs(new QVector<QString>()), conds(new QVector<QString>()),
    days(new QVector<QString>()), temps(new QVector<std::pair<QString,QString> >()) ,tempsMec(new QVector<std::pair<QString,QString> >()),
    tempsImp(new QVector<std::pair<QString,QString> >())    {

    this->id = id;
    this->name = name;

}
/*
 *Copy Constructor
 *Param: City &other - The city to copy
 */
City::City(const City &other) {
    temps = new QVector<std::pair<QString,QString> >(*other.temps);
    imgs = new QVector<QString>(*other.imgs);
    conds = new QVector<QString>(*other.conds);
    days = new QVector<QString>(*other.days);
    tempsMec = new QVector<std::pair<QString, QString> >(*other.tempsMec);
    tempsImp = new QVector<std::pair<QString, QString> >(*other.tempsImp);
    id = other.id;
    name = other.name;
    curTemp = other.curTemp;
    curImpTemp = other.curImpTemp;
    curMetricTemp = other.curMetricTemp;
    curPressure = other.curPressure;
    curImperialPres = other.curImperialPres;
    curHumidity = other.curHumidity;
    curImg = other.curImg;
    curCond = other.curCond;
    curMetricMinMax = other.curMetricMinMax;            //< MinTemp, MaxTemp>
    curImperialMinMax = other.curImperialMinMax;          //< MinTemp, MaxTemp>
    curMinMax = other.curMinMax;
}

/*
 *Destructor
 */
City::~City() {
    delete imgs;
    delete conds;
    delete days;
    delete temps;
    delete tempsMec;
    delete tempsImp;
}
/*
 * Overloaded = operator, see copy constructor
 */

City& City::operator  =(const City& param) {
    if(this != &param) {
        City *tempCity = new City(param);
        return *tempCity;
        delete this;
    }
    return *this;
}
/*
 * Overloaded == operator, compares cities based off id
 * Param: City &param the city to compare to
 */
bool City::operator ==(const City& param) {

    if(this->id == param.id) return true;
    return false;
}

/*
 * Function to load a city given json data for both current and longterm weather
 * Params: QJsonObject &curWea - current weather data, QJsonObject &ltWea - long term weather data
 */
void City::loadCity(const QJsonObject &curWea,const QJsonObject &ltWea) {


    //Set Current Weather Attributes
    if(curWea["message"].toString() == "like") {

        curTemp.setNum(curWea["list"].toArray()[0].toObject()["main"].toObject()["temp"].toDouble(), 'f', 1);
        curMetricTemp.setNum(curWea["list"].toArray()[0].toObject()["main"].toObject()["temp"].toDouble()-273.15, 'f', 1);
        curImpTemp.setNum(curWea["list"].toArray()[0].toObject()["main"].toObject()["temp"].toDouble()*1.8-459.67, 'f', 1);
        curMinMax.first.setNum(curWea["list"].toArray()[0].toObject()["main"].toObject()["temp_min"].toDouble(), 'f', 1);
        curMinMax.second.setNum(curWea["list"].toArray()[0].toObject()["main"].toObject()["temp_max"].toDouble(), 'f', 1);
        curMetricMinMax.first.setNum(curWea["list"].toArray()[0].toObject()["main"].toObject()["temp_min"].toDouble()-273.15, 'f', 1);
        curMetricMinMax.second.setNum(curWea["list"].toArray()[0].toObject()["main"].toObject()["temp_max"].toDouble()-273.15, 'f', 1);
        curImperialMinMax.first.setNum(curWea["list"].toArray()[0].toObject()["main"].toObject()["temp_min"].toDouble()*1.8-459.67, 'f', 1);
        curImperialMinMax.second.setNum(curWea["list"].toArray()[0].toObject()["main"].toObject()["temp_max"].toDouble()*1.8-459.67, 'f', 1);
        curHumidity.setNum(curWea["list"].toArray()[0].toObject()["main"].toObject()["humidity"].toDouble(), 'f', 1);
        curPressure.setNum(curWea["list"].toArray()[0].toObject()["main"].toObject()["pressure"].toDouble()/10, 'f', 1);
        curImperialPres.setNum(curWea["list"].toArray()[0].toObject()["main"].toObject()["pressure"].toDouble()*0.0145, 'f', 1);
        curCond = curWea["list"].toArray()[0].toObject()["weather"].toArray()[0].toObject()["description"].toString();
        curImg = curWea["list"].toArray()[0].toObject()["weather"].toArray()[0].toObject()["icon"].toString() + ".png";
        name = curWea["list"].toArray()[0].toObject()["name"].toString() + "," + curWea["list"].toArray()[0].toObject()["sys"].toObject()["country"].toString();
        id = curWea["list"].toArray()[0].toObject()["id"].toDouble();
    }
    else {

        curTemp.setNum(curWea["main"].toObject()["temp"].toDouble(), 'f', 1);
        curMetricTemp.setNum(curWea["main"].toObject()["temp"].toDouble()-273.15, 'f', 1);
        curImpTemp.setNum(curWea["main"].toObject()["temp"].toDouble()*1.8-459.67, 'f', 1);
        curMinMax.first.setNum(curWea["main"].toObject()["temp_min"].toDouble(), 'f', 1);
        curMinMax.second.setNum(curWea["main"].toObject()["temp_max"].toDouble(), 'f', 1);
        curMetricMinMax.first.setNum(curWea["main"].toObject()["temp_min"].toDouble()-273.15, 'f', 1);
        curMetricMinMax.second.setNum(curWea["main"].toObject()["temp_max"].toDouble()-273.15, 'f', 1);
        curImperialMinMax.first.setNum(curWea["main"].toObject()["temp_min"].toDouble()*1.8-459.67, 'f', 1);
        curImperialMinMax.second.setNum(curWea["main"].toObject()["temp_max"].toDouble()*1.8-459.67, 'f', 1);
        curHumidity.setNum(curWea["main"].toObject()["humidity"].toDouble(), 'f', 1);
        curPressure.setNum(curWea["main"].toObject()["pressure"].toDouble()/10, 'f', 1);
        curImperialPres.setNum(curWea["main"].toObject()["pressure"].toDouble()*0.0145, 'f', 1);
        curCond = curWea["weather"].toArray()[0].toObject()["description"].toString();
        curImg = curWea["weather"].toArray()[0].toObject()["icon"].toString() + ".png";
        name = curWea["name"].toString() + "," + curWea["sys"].toObject()["country"].toString();
        id = curWea["id"].toDouble();

    }
    loadLongTerm(ltWea);

}
/*
 * Private helper function responsible for loading the longterm weather data
 * Param: QJsonObject &ltWea - the long term weather data
 */
void City::loadLongTerm(const QJsonObject &ltWea) {
    //Fetch Long Term Weather Attributes

    //Fetch and convert days

    temps->clear();
    tempsMec->clear();
    tempsImp->clear();
    conds->clear();
    days->clear();
    imgs->clear();


    QVector<QDateTime> *tempdaylist = new QVector<QDateTime>();
    for(int i =0; i < ltWea["list"].toArray().size() ; ++i) {
        QDateTime tempday;
        tempday.setTime_t((uint)ltWea["list"].toArray()[i].toObject()["dt"].toDouble());
        tempdaylist->append(tempday);

        //Fetch min/max temps
        std::pair<QString, QString> temptemppair;
        temptemppair.first.setNum(ltWea["list"].toArray()[i].toObject()["temp"].toObject()["min"].toDouble(), 'f', 1);
        temptemppair.second.setNum(ltWea["list"].toArray()[i].toObject()["temp"].toObject()["max"].toDouble(), 'f', 1);
        temps->append(temptemppair);
        std::pair<QString, QString> temptemppairM;
        temptemppairM.first.setNum(ltWea["list"].toArray()[i].toObject()["temp"].toObject()["min"].toDouble()-273.15, 'f', 1);
        temptemppairM.second.setNum(ltWea["list"].toArray()[i].toObject()["temp"].toObject()["max"].toDouble()-273.15, 'f', 1);
        tempsMec->append(temptemppairM);
        std::pair<QString, QString> temptemppairI;
        temptemppairI.first.setNum(ltWea["list"].toArray()[i].toObject()["temp"].toObject()["min"].toDouble()*1.8-459.67, 'f', 1);
        temptemppairI.second.setNum(ltWea["list"].toArray()[i].toObject()["temp"].toObject()["max"].toDouble()*1.8-459.67, 'f', 1);
        tempsImp->append(temptemppairI);
        //Fetch conditions
        conds->append(ltWea["list"].toArray()[i].toObject()["weather"].toArray()[0].toObject()["main"].toString());
        //Fetch images
        imgs->append(ltWea["list"].toArray()[i].toObject()["weather"].toArray()[0].toObject()["icon"].toString() + ".png");

    }
    generateDays(*tempdaylist);

    delete tempdaylist;
    //std::cout << "finished generating city" << std::endl;
}

/*
 * Helper function to convert from unix time to day,month,date
 * Params: QVector<QDateTime> &daylist - date/time for each day of the forecast
 */
void City::generateDays(const QVector<QDateTime> &daylist)    {
    const int UTCOFFSET = -18000; //Convert from GMT to EST (5 hours in seconds)
    for(QVector<QDateTime>::const_iterator it = daylist.begin(); it != daylist.end(); ++it)
        days->append(it->addSecs(UTCOFFSET).date().toString("ddd.MMM.d"));
}

/*
 * Get the name of the city
 * Return: QString - the name of the city
 */
QString City::getName() {
    return this->name;
}
/*
 * Get the current temperature
 * Return: QString - the current temperature in kelvin
 */
QString City::getCurTemp(){
    return this->curTemp;
}
/*
 * Get the current temperature in metric
 * Return - the current temperature in celsius
 */
QString City::getCurMetricTemp() {
    return curMetricTemp;
}
/*
 * Get the current temperature in imperial
 * Return: QString - the current temperature in fahrenheit
 */
QString City::getCurImperialTemp() {
    return curImpTemp;
}
/*
 * Get the current pressure in imperial
 * Return: QString - the current pressure in psi
 */
QString City::getCurImperialPressure() {
    return curImperialPres;
}
/*
 * Get the current pressure in SI/Metric
 * Return: QString - the current pressure in kPa
 */
QString City::getCurPressure() {
    return curPressure;
}
/*
 * Get the current humidity
 * Return: QString - the current humidity
 */
QString City::getCurHumidity(){
    return curHumidity;
}
/*
 * Get the current weather image
 * Return: QString - the file name of current weather image
 */
QString City::getCurImg() {
    return curImg;
}
/*
 * Get the current condition description
 * Return: QString - the current condition description
 */
QString City::getCurCond() {
    return curCond;
}
/*
 * Get the openweather city id
 * Return: int - the city id
 */
int City::getId() {
    return id;
}
/*
 * Get the current min/max temperatures in kelvin
 * Return: std::pair<QString,QString> the current min/max temperatures
 */
std::pair<QString,QString> City::getCurMinMax() {
    return curMinMax;
}

/*
 * Get the current min/max temperatures in celsius
 * Return: std::pair<QString,QString> the current min/max temperatures
 */
std::pair<QString,QString> City::getCurMetricMinMax() {
    return curMetricMinMax;
}

/*
 * Get the current min/max temperatures in fahrenheit
 * Return: std::pair<QString,QString> the current min/max temperatures
 */
std::pair<QString,QString> City::getCurImperialMinMax() {
    return curImperialMinMax;
}
/*
 * Get the image set for the long term forecast
 * Return: QVector<QString> - Set of file names of long term weather images
 */
QVector<QString> &City::getLtImgs() {
    return *imgs;
}
/*
 * Get the set of long term condition descriptions
 * Return: QVector<QString> - set of long term condition descriptions
 */
QVector<QString> &City::getLtConds() {
    return *conds;
}
/*
 * Get the set of dates for long term forecast
 * Return: QVector<QString> - set of long term forecast dates
 */
QVector<QString> &City::getLtDays() {
    return *days;
}
/*
 * Get the set of long term min/max temps in kelvin
 * Return: QVector<std::pair<QString,QString> > - the set of longterm min/max temperatures
 */
QVector<std::pair<QString,QString> > &City::getLtTemps() {
    return *temps;
}
/*
 * Get the set of long term min/max temps in celsius
 * Return: QVector<std::pair<QString,QString> > - the set of longterm min/max temperatures
 */
QVector<std::pair<QString,QString> > &City::getLtMetricTemps() {
    return *tempsMec;
}
/*
 * Get the set of long term min/max temps in fahrenheit
 * Return: QVector<std::pair<QString,QString> > - the set of longterm min/max temperatures
 */
QVector<std::pair<QString,QString> > &City::getLtImperialTemps() {
    return *tempsImp;
}


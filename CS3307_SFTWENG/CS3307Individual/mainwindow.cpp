/*
 *Author: Alex Clarke
 *File: mainwindow.cpp
 *Description: An openweather compatiable gui to display weather data
 *Date: Oct 4, 2013
 */

#include "mainwindow.h"
#include <iostream>
#include "ui_mainwindow.h"
#include "datamanager.h"
#include "city.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), dMan(new Datamanager(this)) , ui(new Ui::MainWindow) , curCity(new City()) {
    ui->setupUi(this);
    unittype = 0;
    loadUI();
}
/*
 * Destructor
 */
MainWindow::~MainWindow()
{
    delete dMan;
    delete ui;
}
/*
 * Begin loading the ui from saved list
 */
void MainWindow::loadUI() {
    if(loadCityList()) { //If there is at least one saved city, load current weather information and display
        dMan->loadWeatherById(dMan->getCityList()[0].getId());
        ui->loading->setText("Loading Weather");    //Let user know data is loading
        ui->loading->setVisible(true);
        connect(dMan,SIGNAL(dataLoaded()),this,SLOT(dataDownloaded()));
    }
}

/*
 * Load the list of cities and display them to the gui, if there is a city to load make a note of it
 */
bool MainWindow::loadCityList() {
    ui->cityListWidget->clear();
    for(QVector<City>::iterator it = dMan->getCityList().begin(); it != dMan->getCityList().end(); ++it) {
        ui->cityListWidget->addItem(it->getName());
        cityLoaded = true;
    }
    if(dMan->getCityList().isEmpty()) {
        cityLoaded = false;
        return false;
    }
    return true;
}
/*
 * Draw the current weather info
 */
void MainWindow::drawCurrentInfo() {

    switch(unittype) {  //Draw in the correct units, 0 for Metric, 1 for imperial, 2 for SI
        case 0:
        ui->tempLabel->setText("Temperature: " + curCity->getCurMetricTemp() + " °C");
        ui->humidity->setText("Humidity: " + curCity->getCurHumidity() + " %   Pressure: " + curCity->getCurPressure() + " kPa" );
        ui->tempminmax->setText("Min Temp: " + curCity->getCurMetricMinMax().first + " °C   Max Temp: " + curCity->getCurMetricMinMax().second + " °C");
        break;
    case 1:
        ui->tempLabel->setText("Temperature: " + curCity->getCurImperialTemp() + " °F");
        ui->humidity->setText("Humidity: " + curCity->getCurHumidity() + " %   Pressure: " + curCity->getCurImperialPressure() + " psi" );
        ui->tempminmax->setText("Min Temp: " + curCity->getCurImperialMinMax().first + " °F   Max Temp: " + curCity->getCurImperialMinMax().second + " °F");
        break;
    case 2:
        ui->tempLabel->setText("Temperature: " + curCity->getCurTemp() + "K");
        ui->humidity->setText("Humidity: " + curCity->getCurHumidity() + " %   Pressure: " + curCity->getCurPressure() + " kPa" );
        ui->tempminmax->setText("Min Temp: " + curCity->getCurMinMax().first + " K   Max Temp: " + curCity->getCurMinMax().second + " K");
        break;
    default:
        break;
    }
    ui->curCond->setText("Current Condition: " + curCity->getCurCond());
    QPixmap curImg("images/"+curCity->getCurImg());
    ui->weaImg->setPixmap(curImg);
}
/*
 * Draw the long term info
 */
void MainWindow::drawLtInfo() {
    //std::cout << "In lt info" << std::endl;
    ui->d0->setText(curCity->getLtDays()[0]);
    QPixmap temp0("images/" + curCity->getLtImgs()[0]);
    ui->d0Img->setPixmap(temp0);
    ui->d0Cond->setText(curCity->getLtConds()[0]);

    ui->d1->setText(curCity->getLtDays()[1]);
    QPixmap temp1("images/" + curCity->getLtImgs()[1]);
    ui->d1Img->setPixmap(temp1);
    ui->d1Cond->setText(curCity->getLtConds()[1]);

    ui->d2->setText(curCity->getLtDays()[2]);
    QPixmap temp2("images/" + curCity->getLtImgs()[2]);
    ui->d2Img->setPixmap(temp2);
    ui->d2Cond->setText(curCity->getLtConds()[2]);

    ui->d3->setText(curCity->getLtDays()[3]);
    QPixmap temp3("images/" + curCity->getLtImgs()[3]);
    ui->d3Img->setPixmap(temp3);
    ui->d3Cond->setText(curCity->getLtConds()[3]);

    ui->d4->setText(curCity->getLtDays()[4]);
    QPixmap temp4("images/" + curCity->getLtImgs()[4]);
    ui->d4Img->setPixmap(temp4);
    ui->d4Cond->setText(curCity->getLtConds()[4]);

    switch(unittype) {  //Draw in correct units 0 for metric, 1 for imperial, 2 for SI

    case 0:
        ui->d0Temp->setText(curCity->getLtMetricTemps()[0].first + " °C / " + curCity->getLtMetricTemps()[0].second + " °C");
        ui->d1Temp->setText(curCity->getLtMetricTemps()[1].first + " °C / " + curCity->getLtMetricTemps()[1].second + " °C");
        ui->d2Temp->setText(curCity->getLtMetricTemps()[2].first + " °C / " + curCity->getLtMetricTemps()[2].second + " °C");
        ui->d3Temp->setText(curCity->getLtMetricTemps()[3].first + " °C / " + curCity->getLtMetricTemps()[3].second + " °C");
        ui->d4Temp->setText(curCity->getLtMetricTemps()[4].first + " °C / " + curCity->getLtMetricTemps()[4].second + " °C");
        break;
    case 1:
        ui->d0Temp->setText(curCity->getLtImperialTemps()[0].first + " °F / " + curCity->getLtImperialTemps()[0].second + " °F");
        ui->d1Temp->setText(curCity->getLtImperialTemps()[1].first + " °F / " + curCity->getLtImperialTemps()[1].second + " °F");
        ui->d2Temp->setText(curCity->getLtImperialTemps()[2].first + " °F / " + curCity->getLtImperialTemps()[2].second + " °F");
        ui->d3Temp->setText(curCity->getLtImperialTemps()[3].first + " °F / " + curCity->getLtImperialTemps()[3].second + " °F");
        ui->d4Temp->setText(curCity->getLtImperialTemps()[4].first + " °F / " + curCity->getLtImperialTemps()[4].second + " °F");
        break;
    case 2:
        ui->d0Temp->setText(curCity->getLtTemps()[0].first + " K / " + curCity->getLtTemps()[0].second + " K");
        ui->d1Temp->setText(curCity->getLtTemps()[1].first + " K / " + curCity->getLtTemps()[1].second + " K");
        ui->d2Temp->setText(curCity->getLtTemps()[2].first + " K / " + curCity->getLtTemps()[2].second + " K");
        ui->d3Temp->setText(curCity->getLtTemps()[3].first + " K / " + curCity->getLtTemps()[3].second + " K");
        ui->d4Temp->setText(curCity->getLtTemps()[4].first + " K / " + curCity->getLtTemps()[4].second + " K");
        break;
    default:
        break;
      }
    ui->loading->setVisible(false);

}

/*
 * Private slot to handle downloaded data
 */
void MainWindow::dataDownloaded() {
    curCity->loadCity(dMan->getWeatherData().first,dMan->getWeatherData().second); //Give current city raw weather data
    if(curCity->getId() == 0) return; //Catch cases where user has searched for garbage
    ui->curCityLbl->setText(curCity->getName());    //Set the label to the current city's name
    drawCurrentInfo();  //Draw the current weather info
    drawLtInfo();   //Draw the long term weather info
    cityLoaded = true;  //Make a note that there is a city loaded
}
/*
 * Slot to handle selecting metric
 */
void MainWindow::on_metric_clicked()
{
    unittype = 0;
    if(cityLoaded) { //Reload data if there is an active city
        dMan->loadWeatherById(curCity->getId());
        ui->loading->setText("Loading Weather");    //Let user know data is loading
        ui->loading->setVisible(true);
        connect(dMan,SIGNAL(dataLoaded()),this,SLOT(dataDownloaded()));
    }
    return;
}
/*
 * Slot to handle selecting imperial
 */
void MainWindow::on_imperial_clicked()
{
    unittype = 1;
    if(cityLoaded) { //Reload data if there is an active city
        dMan->loadWeatherById(curCity->getId());
        ui->loading->setText("Loading Weather");    //Let user know data is loading
        ui->loading->setVisible(true);
        connect(dMan,SIGNAL(dataLoaded()),this,SLOT(dataDownloaded()));
    }
    return;
}
/*
 * Slot to handle selecting SI
 */
void MainWindow::on_si_clicked()
{
    unittype = 2;
    if(cityLoaded) { //Reload data if there is an active city
        dMan->loadWeatherById(curCity->getId());
        ui->loading->setText("Loading Weather");    //Let user know data is loading
        ui->loading->setVisible(true);
        connect(dMan,SIGNAL(dataLoaded()),this,SLOT(dataDownloaded()));
    }
    return;
}
/*
 * Slot to handle reloading of weather info request
 */
void MainWindow::on_getWea_clicked()
{
    if(cityLoaded) { //Reload data if there is an active city
        dMan->loadWeatherById(curCity->getId());
        ui->loading->setText("Loading Weather");    //Let user know data is loading
        ui->loading->setVisible(true);
        connect(dMan,SIGNAL(dataLoaded()),this,SLOT(dataDownloaded()));
    }
    return;
}
/*
 * Slot to handle if a user presses enter on the search field
 */
void MainWindow::on_searchBar_returnPressed()
{
    if(ui->searchBar->displayText() == "") return; //ensure there is something to look for
    dMan->loadWeatherByName(ui->searchBar->displayText()); //get the text from the field
    ui->loading->setText("Loading Weather");    //Let user know data is loading
    ui->loading->setVisible(true);
    connect(dMan,SIGNAL(dataLoaded()),this,SLOT(dataDownloaded()));

}
/*
 * Slot to handle if a user presses the search button
 */
void MainWindow::on_search_clicked()
{
    if(ui->searchBar->displayText() == "") return; //ensure there is something to look for
    dMan->loadWeatherByName(ui->searchBar->displayText()); //get the text from the field
    ui->loading->setText("Loading Weather");    //Let user know data is loading
    ui->loading->setVisible(true);
    connect(dMan,SIGNAL(dataLoaded()),this,SLOT(dataDownloaded()));
}
/*
 * Slot to handle if a user selects a city on the city list
 */
void MainWindow::on_cityListWidget_itemClicked(QListWidgetItem *item)
{
    dMan->loadWeatherById(dMan->getCityList()[ui->cityListWidget->currentRow()].getId());
    ui->loading->setText("Loading Weather");    //Let user know data is loading
    ui->loading->setVisible(true);
    connect(dMan,SIGNAL(dataLoaded()),this,SLOT(dataDownloaded()));
}
/*
 * Slot to handle if a user tries to add/delete the current city from the city list
 */
void MainWindow::on_adddel_clicked()
{
    int id = dMan->getCityList().indexOf(*curCity);
    if(id != -1) {      // if the city is on the list remove it from the list and remove from city list on screen
        dMan->removeCity(id);
        QListWidgetItem *tempItem = ui->cityListWidget->takeItem(id);
        delete tempItem;
    }
    else {      //else add it to the city list and display on screen
        dMan->addCity(curCity->getId(),curCity->getName());
        ui->cityListWidget->addItem(curCity->getName());
    }

}



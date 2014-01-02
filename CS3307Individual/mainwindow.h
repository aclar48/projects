/*
 *Author: Alex Clarke
 *File: mainwindow.h
 *Description: An openweather compatiable gui to display weather data
 *Date: Oct 4, 2013
 */

#ifndef MAINWINDOW_H
#define MAINWINDOW_H


#include <QMainWindow>
#include <QListWidgetItem>
#include "datamanager.h"
#include "city.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void loadUI();

public slots:


    
private slots:
     void dataDownloaded();

    void on_metric_clicked();

    void on_imperial_clicked();

    void on_si_clicked();

    void on_getWea_clicked();

    void on_searchBar_returnPressed();

    void on_search_clicked();

    void on_cityListWidget_itemClicked(QListWidgetItem *item);

    void on_adddel_clicked();

private:

    Datamanager *dMan;
    Ui::MainWindow *ui;
    City *curCity;
    int unittype;
    bool cityLoaded;

    void drawCurrentInfo();
    void drawLtInfo();
    bool loadCityList();

};

#endif // MAINWINDOW_H

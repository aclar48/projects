/**
  Author: Alex Clarke
  Dec 6 2013

  First ui window
 */
#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "sphere.h"
#include "plane.h"
#include "trace.h"
#include "dialog.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_3_clicked();


    void on_pushButton_2_clicked();

private:
    Ui::MainWindow *ui;
    QVector<Sphere> *_slist;
    QVector<Plane> *_plist;
    QVector<GeoObject *> *_olist;
    int sid, sx, sy, pid;
    Trace *t;
    Dialog *d;
};

#endif // MAINWINDOW_H

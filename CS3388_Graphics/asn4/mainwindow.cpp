/**
  Author: Alex Clarke
  Dec 6 2013

  First ui window
 */
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "trace.h"
#include "light.h"
#include <glm/glm.hpp>
#include <iostream>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow), _slist(new QVector<Sphere>()),_plist(new QVector<Plane>()), _olist(new QVector<GeoObject *>()), d(new Dialog(this))
{
    ui->setupUi(this);

    sx = 600;
    sy = 600;
    Camera c(glm::vec3(0,0,-10),glm::vec3(0,0,0),glm::vec3(0,1,0),10,1.0);
    t = new Trace(c,sx,sy);

    sid = 0;
    pid = 0;

}

MainWindow::~MainWindow()
{
    delete ui;
    delete _slist;
    delete _plist;
}
//Add a sphere of given parameters to the list
void MainWindow::on_pushButton_clicked()
{

    glm::vec3 trans(ui->lineEditxTrans->text().toDouble(),ui->lineEdityTrans->text().toDouble(),ui->lineEditzTrans->text().toDouble());
    glm::vec3 scale(ui->lineEditxScale->text().toDouble(),ui->lineEdityScale->text().toDouble(),ui->lineEditzScale->text().toDouble());
    double rotx = ui->lineEditxRot->text().toDouble();
    double roty = ui->lineEdityRot->text().toDouble();
    double rotz = ui->lineEditzRot->text().toDouble();
    QColor col(ui->lineEditrColour->text().toInt(),ui->lineEditrColourG->text().toInt(),ui->lineEditrColourB->text().toInt());
    double diff = ui->lineEditDiff->text().toDouble();
    double spec = ui->lineEdit->text().toDouble();
    glm::vec3 lightpos(ui->lineEditLightX->text().toDouble(),ui->lineEditLightY->text().toDouble(),ui->lineEditLightZ->text().toDouble());
    Light light(lightpos);
    t->setLight(light);




    Sphere *sp = new Sphere(sid++);
    sp->setType("sphere");
    sp->setTrans(trans);
    sp->setScale(scale);
    sp->setRotatex(rotx);
    sp->setRotatey(roty);
    sp->setRotatez(rotz);
    sp->setColor(col);
    sp->setDiff(diff);
    sp->setSpec(spec);
    _olist->append(sp);
    t->setOlist(_olist);

}
//Trace then open new window to display
void MainWindow::on_pushButton_3_clicked()
{

    d->run(*t,sx,sy);
    d->show();





}


void MainWindow::on_pushButton_2_clicked()
{

    glm::vec3 trans(ui->lineEditxTrans->text().toDouble(),ui->lineEdityTrans->text().toDouble(),ui->lineEditzTrans->text().toDouble());
    glm::vec3 scale(ui->lineEditxScale->text().toDouble(),ui->lineEdityScale->text().toDouble(),ui->lineEditzScale->text().toDouble());
    double rotx = ui->lineEditxRot->text().toDouble();
    double roty = ui->lineEdityRot->text().toDouble();
    double rotz = ui->lineEditzRot->text().toDouble();
    QColor col(ui->lineEditrColour->text().toInt(),ui->lineEditrColourG->text().toInt(),ui->lineEditrColourB->text().toInt());
    double diff = ui->lineEditDiff->text().toDouble();
    double spec = ui->lineEdit->text().toDouble();
    glm::vec3 lightpos(ui->lineEditLightX->text().toDouble(),ui->lineEditLightY->text().toDouble(),ui->lineEditLightZ->text().toDouble());
    Light light(lightpos);
    t->setLight(light);

    Plane *sp = new Plane(sid++);
    sp->setTrans(trans);
    sp->setScale(scale);
    sp->setRotatex(rotx);
    sp->setRotatey(roty);
    sp->setRotatez(rotz);
    sp->setColor(col);
    sp->setDiff(diff);
    sp->setSpec(spec);
    _olist->append(sp);
    t->setOlist(_olist);

}

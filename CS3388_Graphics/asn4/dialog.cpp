/**
  Author: Alex Clarke
  Dec 6 2013

  Dialog displaying the image
 */

#include "dialog.h"
#include "ui_dialog.h"

Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
    ui->setupUi(this);
}

Dialog::Dialog(QWidget *parent, Trace &t, int sx, int sy):
QDialog(parent),
ui(new Ui::Dialog)
{
    ui->setupUi(this);



}
//Ray trace then display
void Dialog::run(Trace &t, int sx, int sy)
{
    QImage *img = new QImage(sx,sy,QImage::Format_RGB16);

    t.run();

    for(int i = 0; i < sx; ++i) {
        for(int j = 0; j < sy; ++j) {
            img->setPixel(i,j,t.pixels()->at(i).at(j).rgb());
        }
    }
    QPixmap *pic = new QPixmap(QPixmap::fromImage(*img));

    ui->label->setPixmap(*pic);
}

Dialog::~Dialog()
{
    delete ui;
}

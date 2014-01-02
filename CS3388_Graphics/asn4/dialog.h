/**
  Author: Alex Clarke
  Dec 6 2013

  Dialog displaying the image
 */
#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>
#include "trace.h"

namespace Ui {
class Dialog;
}

class Dialog : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog(QWidget *parent = 0);
    Dialog(QWidget *parent, Trace &t, int sx, int sy);
    void run(Trace &t, int sx, int sy);
    ~Dialog();


private:
    Ui::Dialog *ui;
};

#endif // DIALOG_H

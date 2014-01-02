/**
  Author: Alex Clarke
  Dec 6 2013

  Start the ui
 */
#include "mainwindow.h"
#include <QApplication>
#include "trace.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();



    return a.exec();
}

/**
  @file displaywindow.cpp
  @author Alex Clarke, Melanie Imough
  @version 1.0

  @class DisplayWindow
  @brief Class for a generic tabbed data viewing window

  Creates a window in which various chart or table widgets can exist.

  */

#include "displaywindow.h"
#include "ui_displaywindow.h"
/**
 * @brief DisplayWindow::DisplayWindow Default Constructor
 * @param parent
 */
DisplayWindow::DisplayWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::DisplayWindow)
{
    ui->setupUi(this);
    ui->tabWidget->setTabsClosable(true);
    ui->tabWidget->setMovable(true);
    this->setWindowModality(Qt::NonModal);
}
/**
 * @brief DisplayWindow::~DisplayWindow Deconstructor
 */
DisplayWindow::~DisplayWindow()
{
    delete ui;
}
/**
 * @brief DisplayWindow::addTab Add a tab, the display it
 *
 * The new tab will be, in this application, a bar chart, line chart, or table chart widget.
 *
 * @param newTab the tab to add, using polymorphism to create the different kinds of tab.
 * @param name the tab's name
 */

void DisplayWindow::addTab(QWidget *newTab, const QString &name)
{
    ui->tabWidget->addTab(newTab,name);
    ui->tabWidget->setCurrentIndex(ui->tabWidget->count()-1);
}

/**
 * @brief DisplayWindow::on_tabWidget_tabCloseRequested Permanently delete a tab if you close it
 * @param index
 */
void DisplayWindow::on_tabWidget_tabCloseRequested(int index)
{
    delete ui->tabWidget->widget(index);
}

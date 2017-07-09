#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "QPushButton"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QPushButton* button = new QPushButton(this);
    button->setText("TEST");
    QString abc;

}

MainWindow::~MainWindow()
{
    delete ui;
}

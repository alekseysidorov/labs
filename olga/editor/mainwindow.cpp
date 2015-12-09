#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "paintwidget.h"
#include "figures.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    PaintWidget *wgt = new PaintWidget(this);
    ui->verticalLayout->addWidget(wgt);
}

MainWindow::~MainWindow()
{
    delete ui;
}

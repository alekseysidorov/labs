#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "paintwidget.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    wgt = new PaintWidget(this);
    ui->horizontalLayout->addWidget( wgt);
}

MainWindow::~MainWindow()
{
    delete ui;
}

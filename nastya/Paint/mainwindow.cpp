#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QImage>
#include <random>
#include <QTime>
#include "figures.h"
#include <QString>
#include <QDir>
#include <QSettings>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // Создаем виджет
    wgt = new QPaintWidget(this);

    // И кладём его в лайаут
    ui->verticalLayout->addWidget(wgt);
    connect(ui->pushButton_3, &QPushButton::clicked, this, &MainWindow::clear);
    connect(ui->pushButton, &QPushButton::clicked, this, &MainWindow::save);
    connect(ui->pushButton_2, &QPushButton::clicked, this, &MainWindow::gener);
    connect(ui->pushButton_4, &QPushButton::clicked, this, &MainWindow::download);
}

MainWindow::~MainWindow()
{
    // Подчищаем
    wgt->deleteLater();
    delete ui;
}

void MainWindow::clear()
{
    wgt->clear();
}

void MainWindow::save()
{
    QDir fi = QDir::home();
    wgt->save(fi.absoluteFilePath("Pictures/"));
}

void MainWindow::gener()
{
    wgt->pr = 0;
}

void MainWindow::download()
{
    QDir fi = QDir::home();
    wgt->download(fi.absoluteFilePath("Pictures/"));
}

QPaintWidget *MainWindow::wgtt()
{
    return wgt;
}

void MainWindow::changeEvent(QEvent *e)
{
    QMainWindow::changeEvent(e);
    switch (e->type()) {
    case QEvent::LanguageChange:
        ui->retranslateUi(this);
        break;
    default:
        break;
    }
}

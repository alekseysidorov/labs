#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QImage>
#include <random>
#include <QTime>
#include "figures.h"
#include <QString>
#include <QDir>
#include <QSettings>
#include <thread.h>
#include <QFileDialog>

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
    wgt->deleteLater();
    delete ui;
}

void MainWindow::clear()
{
    wgt->clear();
}

void MainWindow::save()
{
    QString d = QFileDialog::getExistingDirectory(this, "some pretty message", QDir::homePath(), QFileDialog::ShowDirsOnly);
    wgt->save(d);
}

void MainWindow::gener()
{
    wgt->pr = 0;
}

void MainWindow::download()
{
    QString d = QFileDialog::getExistingDirectory(this, "some pretty message" ,QDir::homePath(), QFileDialog::ShowDirsOnly | QFileDialog::ReadOnly);
    wgt->download(d);
}

int MainWindow::Tra()
{
    return traa;
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

void MainWindow::closeEvent(QCloseEvent *)
{
    traa = 0;
}

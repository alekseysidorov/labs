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
    wgt->figures.clear();
    wgt->onFigures.clear();
    wgt->update();
}

void MainWindow::save()
{
    QDir fi = QDir::home();
    QDir gg(fi.absoluteFilePath("Pictures/"));
    gg.removeRecursively();
    for (int i = 0; i < wgt->figures.size(); ++i)
    {
        QString d = gg.absoluteFilePath(wgt->figures[i]->name + ".conf");
        wgt->figures[i]->save(d);
    }
}

void MainWindow::gener()
{
    wgt->pr = 0;
}

void MainWindow::download()
{
    QDir fi = QDir::home();
    QDir di(fi.absoluteFilePath("Pictures/"));
    for (auto ci : di.entryInfoList())
    {
        QSettings param(ci.absoluteFilePath(), QSettings::IniFormat);
        param.setIniCodec("UTF8");
        if (param.value("Type") == "circle")
        {
        Circle *c = new Circle(param.value("X").toInt(), param.value("Y").toInt(), param.value("Radius").toInt(), param.value("Color").toString(), param.value("Name").toString());
        wgt->figures.append(c);
    }
        if (param.value("Type") == "rectangle")
        {
            Rectanglee *k = new Rectanglee(param.value("X").toInt(), param.value("Y").toInt(), param.value("Width").toInt(), param.value("Height").toInt(), param.value("Color").toString(), param.value("Name").toString());
            wgt->figures.append(k);
        }
    }
    wgt->update();
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

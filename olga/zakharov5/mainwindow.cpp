#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "paintwidget.h"
#include "generator.h"

#include <QFileDialog>
#include <QKeyEvent>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    wgt = new PaintWidget(this);
    ui->verticalLayout->addWidget(wgt);

    connect(ui->pushButton_2, &QPushButton::clicked, this, &MainWindow::start);
    connect(ui->pushButton, &QPushButton::clicked, this, &MainWindow::save);

    generator = new Generator();
    connect(generator, &Generator::painted, wgt, &PaintWidget::paint);
    generator->start();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::start()
{
    generator->paused = false;
}

void MainWindow::save()
{
    generator->paused = true;

    QString fileName = QFileDialog::getSaveFileName(this, tr("Save File"),
                                                    "~",
                                                    tr("Images (*.png *.xpm *.jpg)"));

    wgt->image.save(fileName);
}

void MainWindow::keyPressEvent(QKeyEvent *e)
{
    if (e->key() == Qt::Key_Space) {
        generator->paused = true;
    }
}


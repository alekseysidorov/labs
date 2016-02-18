#include "mainwindow.h"
#include "ui_mainwindow.h"

const int n = 3; // размер игрового поля

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            Cell *c = new Cell(this);
            c->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
            ui->gridLayout->addWidget(c, i, j);
            m_cells.push_back(c);
            connect(c, &Cell::clicked, this, &MainWindow::onClicked);
        }
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}

Cell *MainWindow::cellAt(int i, int j)
{
    return m_cells[i * n + j];
}

bool MainWindow::canTurn(int i, int j)
{
    // проверяем границы, если заведомо за них вылезаем, то ходить не можем
    if (i < 0 || j < 0 || i >= n || j >= n)
        return false;
    // ходить мы можем только в пустую клетку
    return cellAt(i, j)->status() == Cell::None;
}

void MainWindow::onClicked()
{
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            if (canTurn(i, j)) {
                cellAt(i, j)->tack();
                return;
            }
        }
    }
}

Cell::Cell(QWidget *p) : QPushButton(p)
{
    connect(this, &Cell::clicked, this, &Cell::onClicked);
}

void Cell::tick()
{
    setText("X");
    setEnabled(false);
    m_status = Tick;
}

void Cell::tack()
{
    setText("O");
    setEnabled(false);
    m_status = Tack;
}

Cell::Status Cell::status()
{
    return m_status;
}

void Cell::onClicked()
{
    tick(); // Игрок играет за крестики
}

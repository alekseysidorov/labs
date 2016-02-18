#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    m_field(n)
{
    m_player = Field::Tick;

    ui->setupUi(this);

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            QPushButton *c = new QPushButton(this);
            c->setProperty("i", i);
            c->setProperty("j", j);
            c->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
            ui->gridLayout->addWidget(c, i, j);
            m_cells.push_back(c);
            connect(c, &QPushButton::clicked, this, &MainWindow::onClicked);
        }
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}

QPushButton *MainWindow::cellAt(int i, int j)
{
    return m_cells[i * n + j];
}

void MainWindow::onClicked()
{
    QObject *s = sender();
    int i = s->property("i").toInt();
    int j = s->property("j").toInt();

    m_field.setStatus(i, j, m_player);
    update();

    // ход компьютера
}

void MainWindow::update()
{
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            QPushButton *c = cellAt(i, j);

            Field::Status s = m_field.statusAt(i, j);
            if (s == Field::Tick) {
                c->setText("X");
                c->setEnabled(false);
            } else if (s == Field::Tack) {
                c->setText("O");
                c->setEnabled(false);
            }
        }
    }
}

Field::Field(int s)
{
    m_size = s;
    m_statuses.resize(s * s);
}

Field::Status Field::statusAt(int i, int j)
{
    return m_statuses[i * m_size + j];
}

void Field::setStatus(int i, int j, Field::Status status)
{
    m_statuses[i * m_size + j] = status;
}

bool Field::canTurn(int i, int j)
{
    // проверяем границы, если заведомо за них вылезаем, то ходить не можем
    if (i < 0 || j < 0 || i >= n || j >= n)
        return false;
    // ходить мы можем только в пустую клетку
    return statusAt(i, j) == None;
}

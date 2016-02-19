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

int MainWindow::minMax(Field::Status player, Field field, int depth)
{
    // больше ходить некуда, возвращаем оценку
    if (field.isTerminal(player))
        return field.heuristic(player);

    int score = INT_MIN;
    for (Field child : field.children(player)) {
        int s = maxMin(player, child, depth + 1);
        score = std::max(s, score);
    }
    return score;
}

int MainWindow::maxMin(Field::Status player, Field field, int depth)
{
    // больше ходить некуда, возвращаем оценку
    if (field.isTerminal(player))
        return field.heuristic(player);

    int score = INT_MAX;
    for (Field child : field.children(player)) {
        int s = minMax(player, child, depth + 1);
        score = std::max(s, score);
    }
    return score;
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

// список всех возможных ходов, которые можно сделать для игрока
// версия совсем в лоб
QVector<Field> Field::children(Field::Status player)
{
    QVector<Field> c;
    for (int i = 0; i < m_size; ++i) {
        for (int j = 0; j < m_size; ++j) {
            if (canTurn(i, j)) {
                // делаем копию текущего поля
                Field o = *this;
                c.push_back(o);
            }
        }
    }
    return c;
}

// функция по очкам определяет насколько хорош данный расклад (максимально длинная штука)
int Field::heuristic(Field::Status player)
{
    int s = diagSum(player, 0, 0, 1, 1);
    int res = s;
    s = diagSum(player, m_size - 1, 0, -1, 1); // считаем вторую диагональ
    res = std::max(s, res); // выбираем самую длинную

    // считаем столбцы
    for (int i = 0; i < m_size; ++i) {
        s = diagSum(player, i, 0, 0, 1);
        res = std::max(s, res);
    }

    // считаем строки
    for (int i = 0; i < m_size; ++i) {
        s = diagSum(player, 0, i, 1, 0);
        res = std::max(s, res);
    }

    return res;
}

bool Field::isTerminal(Field::Status player)
{
    if (heuristic(player) == m_size)
        return true; // игрок победил
    if (heuristic(-player) == m_size)
        return true; // победил противник

    for (int i = 0; i < m_size; ++i) {
        for (int j = 0; j < m_size; ++j) {
            if (statusAt(i, j) == None)
                return false;
        }
    }
    return true;
}

// считает сумму диагоналей, i, j точка старта в x, y лежит направление
// также можно и обычные линии считать, если x или y задавать нулевыми
int Field::diagSum(Field::Status player, int i, int j, int x, int y)
{
    int sum = 0;
    while (sum < 3) {
        if (statusAt(i, j) == player)
            ++sum;
        i += x; j += y;

        if (i < 0 || j < 0 || i >= n || j >= n)
            break;
    }
}

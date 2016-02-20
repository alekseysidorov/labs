#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QDebug>

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

    newGame();
    connect(ui->pushButton, &QPushButton::clicked, this, &MainWindow::newGame);
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

    m_field.turn(i, j, m_player);
    // обновляем интерфейс
    update();

    // проверяем что игра еще не закончилась
    if (gameOver())
        return;

    qDebug() << "player: " << m_field.heuristic(m_player);
    qDebug() << "computer: " << m_field.heuristic(-m_player);

    // ход компьютера
    int m_computer = -m_player;
    // считаем возможные ходы и их оценки
    QVector<Turn> turns;
    for (auto child : m_field.children(m_computer)) {
        Turn turn;
        turn.field = child;
        turn.score = max(m_computer, child, 0);
        turns.push_back(turn);
    }

    // делаем ход компьютера, если есть возможность
    if (!turns.isEmpty()) {
        // сортируем ходы (если они есть)
        std::sort(turns.begin(), turns.end());
        m_field = turns.last().field; // берем самый лучший ход
        // обновляем интерфейс
        update();
        if (gameOver())
            return;
    }
}

void MainWindow::update()
{
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            QPushButton *c = cellAt(i, j);

            int s = m_field.statusAt(i, j);
            if (s == Field::Tick) {
                c->setText("X");
                c->setEnabled(false);
            } else if (s == Field::Tack) {
                c->setText("O");
                c->setEnabled(false);
            } else {
                c->setText("");
                c->setEnabled(true);
            }
        }
    }
}

void MainWindow::newGame()
{
    ui->pushButton->setEnabled(false);
    ui->comboBox->setEnabled(false);
    ui->label->setText("");

    if (ui->comboBox->currentIndex() == 0)
        m_player = Field::Tick;
    else
        m_player = Field::Tack;

    m_field = Field(n);
    update();
}

// Проверка что игра закончилась
bool MainWindow::gameOver()
{
    // игра закончилась
    if (m_field.heuristic(m_player) == m_field.size
            || m_field.heuristic(-m_player) == m_field.size) {
       //считаем очки
        int score = m_field.heuristic(m_player);
        if (score == m_field.size)
            ui->label->setText("Игрок выиграл");
        else
            ui->label->setText("Компьютер выиграл");

        ui->pushButton->setEnabled(true);
        ui->comboBox->setEnabled(true);
        return true;
    }
    return false;
}

int MainWindow::max(int player, Field field, int depth)
{
    // больше ходить некуда, возвращаем оценку
    if (field.isTerminal(player, depth))
        return field.heuristic(player);

    int score = INT_MIN;
    for (Field child : field.children(player)) {
        int s = min(-player, child, depth + 1);
        score = std::max(s, score);
    }
    return score;
}

int MainWindow::min(int player, Field field, int depth)
{
    // больше ходить некуда, возвращаем оценку
    if (field.isTerminal(player, depth))
        return -field.heuristic(player);

    int score = INT_MAX;
    for (Field child : field.children(player)) {
        int s = max(-player, child, depth + 1);
        score = std::min(s, score);
    }
    return score;
}

Field::Field(int s)
{
    size = s;
    m_statuses.resize(s * s);
}

int Field::statusAt(int i, int j)
{
    return m_statuses[i * size + j];
}

void Field::turn(int i, int j, int status)
{
    m_statuses[i * size + j] = status;
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
QVector<Field> Field::children(int player)
{
    QVector<Field> c;
    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) {
            if (canTurn(i, j)) {
                // делаем копию текущего поля
                Field o = *this;
                // и ходим
                o.turn(i, j, player);
                c.push_back(o);
            }
        }
    }
    return c;
}


int Field::heuristic(int player)
{
    if (maxSum(-player) == size)
        return -size;
    return maxSum(player);
}

// функция по очкам определяет насколько хорош данный расклад (максимально длинная штука)
int Field::maxSum(int player)
{
    int s = diagSum(player, 0, 0, 1, 1);
    int res = s;
    s = diagSum(player, size - 1, 0, -1, 1); // считаем вторую диагональ
    res = std::max(s, res); // выбираем самую длинную

    // считаем столбцы
    for (int i = 0; i < size; ++i) {
        s = diagSum(player, i, 0, 0, 1);
        res = std::max(s, res);
    }

    // считаем строки
    for (int i = 0; i < size; ++i) {
        s = diagSum(player, 0, i, 1, 0);
        res = std::max(s, res);
    }

    return res;
}

bool Field::isTerminal(int player, int depth)
{
    if (depth >= (size + 2))
        return true;

    if (heuristic(player) == size)
        return true; // игрок победил
    if (heuristic(-player) == size)
        return true; // противник победил

    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) {
            if (statusAt(i, j) == None)
                return false;
        }
    }
    return true;
}

// считает сумму диагоналей, i, j точка старта в x, y лежит направление
// также можно и обычные линии считать, если x или y задавать нулевыми
int Field::diagSum(int player, int i, int j, int x, int y)
{
    int sum = 0;
    while (sum < size) {
        if (statusAt(i, j) == player)
            ++sum;
        i += x; j += y;

        if (i < 0 || j < 0 || i >= n || j >= n)
            break;
    }
    return sum;
}

bool operator<(const Turn &a, const Turn &b)
{
    return a.score < b.score;
}

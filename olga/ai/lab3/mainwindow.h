#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPushButton>

const int n = 3; // размер игрового поля

namespace Ui {
class MainWindow;
}

class Field
{
public:
    int size;

    // для удобства чтобы можно было игроков не просто цифрами величать
    enum Status {
        None = 0,
        Tick = 1, // крестик
        Tack = -1 // нолик
    };

    Field(int s = n);

    int statusAt(int i, int j);
    void turn(int i, int j, int status);
    bool canTurn(int i, int j);

    QVector<Field> children(int player);
    int heuristic(int player);
    bool isTerminal(int player);

    int diagSum(int player, int i, int j, int x, int y);
private:
    QVector<int> m_statuses;
};

// структура для шага, в ней следующее состояние поля и оценка для него
struct Turn
{
    Field field;
    int score;
};

// оператор сравнения (нужен для сортировки)
bool operator<(const Turn &a, const Turn &b);

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    QPushButton *cellAt(int i, int j);
private:
    void onClicked();
    void update();
    void newGame();

    int minMax(int player, Field field, int depth);
    int maxMin(int player, Field field, int depth);

    Ui::MainWindow *ui;

    QList<QPushButton*> m_cells;
    Field m_field;
    Field::Status m_player;

};

#endif // MAINWINDOW_H

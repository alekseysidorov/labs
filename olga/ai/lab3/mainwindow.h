#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPushButton>

namespace Ui {
class MainWindow;
}

class Cell : public QPushButton
{
    Q_OBJECT
public:
    enum Status {
        None,
        Tick, // крестик
        Tack // нолик
    };

    Cell(QWidget *p);

    void tick();
    void tack();

    Status status();
private:
    void onClicked();

    Status m_status = None;
};

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    Cell *cellAt(int i, int j);
    bool canTurn(int i, int j);
private:
    void onClicked();

    Ui::MainWindow *ui;

    QList<Cell*> m_cells;
};

#endif // MAINWINDOW_H

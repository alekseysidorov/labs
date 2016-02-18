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
    enum Status {
        None = 0,
        Tick = 1, // крестик
        Tack = -1 // нолик
    };

    Field(int s);

    Status statusAt(int i, int j);
    void setStatus(int i, int j, Status status);
    bool canTurn(int i, int j);
private:
    int m_size;
    QVector<Status> m_statuses;
};

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

    Ui::MainWindow *ui;

    QList<QPushButton*> m_cells;
    Field m_field;
    Field::Status m_player;

};

#endif // MAINWINDOW_H

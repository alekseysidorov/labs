#include "notepad.h"
#include "ui_notepad.h"

#include <QDateTime>

NotePad::NotePad(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::NotePad)
{
    ui->setupUi(this);

    // Создать новый документ это по сути очистить содержимое текущего
    connect(ui->create, &QAction::triggered, ui->textEdit, &QPlainTextEdit::clear);

    // Всякая копипаста уже есть готовая в QPlainTextEdit, нужно только подсоединить её
    connect(ui->cut, &QAction::triggered, ui->textEdit, &QPlainTextEdit::cut);
    connect(ui->copy, &QAction::triggered, ui->textEdit, &QPlainTextEdit::copy);
    connect(ui->paste, &QAction::triggered, ui->textEdit, &QPlainTextEdit::paste);
    connect(ui->selectAll, &QAction::triggered, ui->textEdit, &QPlainTextEdit::selectAll);

    // undo, redo тоже, что заметно упрощает работу
    connect(ui->undo, &QAction::triggered, ui->textEdit, &QPlainTextEdit::undo);
    connect(ui->redo, &QAction::triggered, ui->textEdit, &QPlainTextEdit::redo);

    // А так мы просим приложение закрыться. Есть у него такой специальный слот quit
    connect(ui->exit, &QAction::triggered, qApp, &QCoreApplication::quit);

    // Делаем кнопку: добавить время
    connect(ui->addDate, &QAction::triggered, this, &NotePad::addDate);

    // Связываем нажатость кнопки с видимостью статусбара
    connect(ui->showStatusBar, &QAction::toggled, ui->statusBar, &QWidget::setVisible);

    // Немного шика - обходим все пункты меню и делаем так, чтобы их вызов отображался в статусбаре
    foreach (QAction *action, ui->menu_2->actions()) {
        connect(action, &QAction::triggered, this, &NotePad::logAction);
    }
}

NotePad::~NotePad()
{
    delete ui;
}

void NotePad::addDate()
{
    QString d = QDateTime::currentDateTime().toString();
    ui->textEdit->insertPlainText(d);
}

void NotePad::logAction()
{
    QAction *a = static_cast<QAction*>(sender());

    ui->statusBar->showMessage("Последнее совершенное действие: " + a->text());
}



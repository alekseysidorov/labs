#ifndef PAINTWIDGET_H
#define PAINTWIDGET_H
#include <QWidget>

struct Figure;

class PaintWidget : public QWidget
{
public:
    QList<Figure*> figures;

    PaintWidget(QWidget *parent = 0);
    ~PaintWidget();

    void load(const QString &fileName);
    void save(const QString &fileName);
protected:
    void paintEvent(QPaintEvent *);
};

#endif // PAINTWIDGET_H

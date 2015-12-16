#ifndef PAINTWIGET_H
#define PAINTWIGET_H

#include <QWidget>

class PaintWidget : public QWidget
{
    Q_OBJECT
public:
    explicit PaintWidget(QWidget *parent = 0);

    QImage image;
signals:

public slots:
    void paint(const QImage &pixmap);
protected:
    void paintEvent(QPaintEvent *);
};

#endif // PAINTWIGET_H

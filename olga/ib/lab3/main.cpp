#include <QString>
#include <QFile>
#include <QTextStream>
#include <QDebug>
#include <QBitArray>

#include <iostream>

QList<int> loadFile(const QString &fileName)
{
    QFile file(fileName);
    file.open(QFile::ReadOnly|QFile::Text);

    QString str = file.readAll();
    str = str.remove("z=[").remove("];");

    QStringList strs = str.split(" ");

    QList<int> vec;
    for (QString s : strs)
        vec.push_back(s.toInt());
    return vec;
}

int main(int, char **)
{
    auto z = loadFile("txt/test.txt");

    // выводим исходный массив z
    std::cout << "z = [";
    for (int i = 0; i < z.size(); ++i)
        std::cout << " " << z[i];
    std::cout << " ];" << std::endl;

    // начальные условия
    int r = 0;
    QList<int> c = {
        1
    };
    QList<int> b = c;

    int d = 0;
    int n =  z.size();
    do {
        ++r;
        // расширяем c
        while (c.size() < r)
            c.push_back(0);

        // вычисляем невязку
        d = 0;
        for (int j = 0; j < r; ++j) {
            d = (d + c[j] * z[r - 1 - j]) % 2;
        }

        b.prepend(0);
        // если не нулевая невязка
        if (d > 0) {
            // формируем новый полином
            QList<int> t;

            // суммируем два полинома
            int size = 0;
            if (c.size() < b.size()) {
                t = b;
                size = c.size();
            } else {
                t = c;
                size = b.size();
            }

            for (int i = 0; i < size; ++i) {
                t[i] = (b[i] + c[i]) % 2;
            }

            b = c; // сохраняем предыдущий полином
            c = t; // меняем связи регистра
        }
    } while (r < n);

    // выводим значение полинома
    std::cout << "c(x) = ";
    if (c[0] == 1)
        std::cout << "1 ";
    for (int i = 1; i < c.size(); ++i) {
        if (c[i] == 1) {
            std::cout << " + x^" << i;
        }
    }
    std::cout << std::endl;

    // выводим L
    for (int i = c.size() / 2; i >= 0; --i) {
        if (c[i] == 1) {
            std::cout << "L = " << i << std::endl;
            break;
        }
    }
}

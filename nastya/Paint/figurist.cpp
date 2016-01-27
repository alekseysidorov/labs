#include "figlibrary.h"
#include <iostream>
#include <QDebug>

int main(int argc, char *argv[])
{
    std::string s, ss;
    std::cin >> s >> ss;
    QString pp = QString::fromStdString(ss);
    if (s == "l") {
        FigLibrary figa;
        figa.load(pp);

        std::cout << "Figs" << std::endl;
        for (int i = 0; i < figa.figss().size(); ++i) {
            Figure *f = figa.figss()[i];
            std::cout << "\ntyp: " << f->typ().toStdString() << "\n"
                      << "nam:" << f->nam().toStdString() << "\n"
                      << "x: " << f->x() << "\n"
                      << "y: " << f->y() << "\n"
                      << "angl: " << f->angl() << "\n"
                      << "col: " << f->col().toStdString() << std::endl;
        }
    }else if (s == "s"){
        FigLibrary figa;
        int n;
        std::cin >> n;
        for (int i = 0; i < n; ++i) {
            std::cin >> s;
            if (s == "circl") {
                int x, y, d;
                std::string nam, cc;
                std::cin >> nam >> cc >> x >> y >> d;
                Circle *c = new Circle(x, y, d, QString::fromStdString(cc), QString::fromStdString(nam));
                figa.add(c);
            }else if(s == "rect"){
                int x, y, w,h;
                double a;
                std::string nam, cc;
                std::cin >> nam >> cc >> x >> y >> w >> h >> a;
                Rectanglee *r = new Rectanglee(x, y, w, h, QString::fromStdString(cc), QString::fromStdString(nam));
                r->setAngl(a);
                figa.add(r);
            }else if(s == "star"){
                int x, y, r; double a;
                std::string nam, cc;
                std::cin >> nam >> cc >> x >> y >> r >> a;
                Star *sss = new Star(x, y,QString::fromStdString(cc), QString::fromStdString(nam), r);
                sss->setAngl(a);
                figa.add(sss);
            }
        }
        figa.save(pp);
    }
}

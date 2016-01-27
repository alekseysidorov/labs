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

        for (int i = 0; i < figa.figss().size(); ++i) {
            Figure *f = figa.figss()[i];
            std::cout << f->nam().toStdString() << "\n"
                      << "x: " << f->x() << "\n"
                      << "y: " << f->y() << "\n"
                      << "angl: " << f->angl() << "\n"
                      << "col: " << f->col().toStdString() << "\n";
        }
    }else if (s == "s"){
        int n;
        std::cin >> n;
        for (int i = 0; i < n; ++i) {
            std::cin >> s;
            if (s == "circl") {

            }else if(s == "rect"){

            }else if(s == "star"){

            }
        }
    }
}

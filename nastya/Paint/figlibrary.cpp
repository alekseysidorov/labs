#include "figlibrary.h"

#include <QSettings>

FigLibrary::FigLibrary()
{

}

void FigLibrary::add(Figure *fi)
{
    figs.push_back(fi);
}

void FigLibrary::remove(int i)
{
    figs.removeAt(i);
}

QList<Figure *> FigLibrary::figss()
{
    return figs;
}

void FigLibrary::load(QString pp)
{
    QDir di(pp);
    for (auto ci : di.entryInfoList())
    {
        QSettings param(ci.absoluteFilePath(), QSettings::IniFormat);
        param.setIniCodec("UTF8");
        if (param.value("Type") == "circle")
        {
        Circle *c = new Circle(param.value("X").toInt(), param.value("Y").toInt(), param.value("Radius").toInt(), param.value("Color").toString(), param.value("Name").toString());
        add(c);
    }
        if (param.value("Type") == "rectangle")
        {
            Rectanglee *k = new Rectanglee(param.value("X").toInt(), param.value("Y").toInt(), param.value("Width").toInt(), param.value("Height").toInt(), param.value("Color").toString(), param.value("Name").toString());
            add(k);
        }
        if (param.value("Type") == "star")
        {
            Star *s = new Star(param.value("X").toInt(), param.value("Y").toInt(), param.value("Color").toString(), param.value("Name").toString(), param.value("Diameter").toInt());
        add(s);}
    }
}

void FigLibrary::save(QString ss)
{
    QDir gg(ss);
    gg.removeRecursively();
    for (int i = 0; i < figs.size(); ++i)
    {
        QString d = gg.absoluteFilePath(figs[i]->nam() + ".conf");
        figs[i]->save(d);
    }
}

void FigLibrary::clear()
{
    for (int i = 0; i < figs.size(); ++i)
        delete figs[i];
    figs.clear();
}

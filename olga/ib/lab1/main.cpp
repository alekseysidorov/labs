#include <QString>
#include <QFile>
#include <QTextStream>
#include <QSet>
#include <QDebug>

QString loadFile(const QString &name)
{
    QFile f(name);
    f.open(QFile::ReadOnly|QFile::Text);
    return f.readAll();
}

void saveFile(const QString &name, const QString &data)
{
    QFile f(name);
    f.open(QFile::WriteOnly|QFile::Text);
    f.write(data.toUtf8());
}

QSet<QString> loadDict(QString words)
{
    QSet<QString> dict;
    QTextStream in(&words);
    while (!in.atEnd()) {
        QString s;
        in >> s;
        s = s.replace("ё", "е");

        QString word;
        for (int i = 0; i < s.size(); ++i) {
            QChar ch = s[i];
            ushort u = ch.unicode();
            if (u >= L'а' && u <= L'я') {
                word.append(ch);
            }
        }
        dict.insert(word);
    }
    return dict;
}

struct Frequency {
    QChar symbol;
    qreal frequency;
};
typedef QList<Frequency> Frequencies;

bool operator<(const Frequency &a, const Frequency &b)
{
    return a.frequency > b.frequency;
}

Frequencies getFrequencies(QString words)
{
    ushort counts[32] = {};
    int total = 0;
    for (int i = 0; i < words.size(); ++i) {
        QChar ch = words[i];
        ushort u = ch.unicode();
        if (u >= L'а' && u <= L'я') {
            u -= L'а';
            counts[u]++;
            total++;
        }
    }

    QList<Frequency> freqs;
    for (ushort w = 0; w < 32; ++w) {
        Frequency f;
        f.symbol = L'а' + w;
        f.frequency = qreal(counts[w]) / total;
        freqs.push_back(f);
    }
    std::sort(freqs.begin(), freqs.end());
    return freqs;
}

QString encryptCaesar(int shift, const QString &string)
{
    QString out;
    for (int i = 0; i < string.size(); ++i) {
        QChar ch = string[i];
        ushort &u = ch.unicode();

        if (u >= L'а' && u <= L'я') {
            u += shift;
            if (u > L'я')
                u -= (L'я' - L'а' + 1);
            if (u < L'а')
                u += (L'я' - L'а' + 1);
        }
        if (u >= L'А' && u <= L'Я') {
            u += shift;
            if (u > L'Я')
                u -= (L'Я' - L'А' + 1);
            if (u < L'А')
                u += (L'Я' - L'А' + 1);
        }
        out.append(ch);
    }
    return out;
}

QString decryptCaesar(const QSet<QString> &dict, QString str)
{
    QTextStream in(&str);

    int shift = 0;
    bool found = false;
    while (!in.atEnd()) {
        QString str;
        in >> str;
        if (str.size() > 3) {
            for (int i = 1; i <= 33; ++i) {
                QString d = encryptCaesar(i, str);
                if (dict.contains(d)) {
                    found = true;
                    shift = i;
                    break;
                }
            }

            if (found)
                break;
        }
    }

    QString out;
    if (found)
        out = encryptCaesar(shift, str);
    return out;
}

QString encryptCiph(ushort *dict, const QString &s)
{
    QString out;
    for (int i = 0; i < s.size(); ++i) {
        QChar ch = s[i];
        ushort &u = ch.unicode();
        if (u >= L'а' && u <= L'я') {
            ushort j = u - L'а';
            u = dict[j];
        }
        out.append(ch);
    }

    return out;
}

QString decryptCiph(QString str)
{
    QString s = loadFile("txt/book.txt");

    Frequencies dictFreqs = getFrequencies(s);
    QSet<QString> dict = loadDict(s);

    ushort table[33] = {
        L'а',
        L'б',
        L'в',
        L'г',
        L'д',
        L'е',
        L'ж',
        L'з',
        L'и',
        L'й',
        L'к',
        L'л',
        L'м',
        L'н',
        L'о',
        L'п',
        L'р',
        L'с',
        L'т',
        L'у',
        L'ф',
        L'х',
        L'ц',
        L'ч',
        L'ш',
        L'щ',
        L'ъ',
        L'ы',
        L'ь',
        L'э',
        L'ю',
        L'я',
    };

    return s;
}

int main(int, char **)
{
    QString txt = loadFile("txt/text.txt");
    txt = encryptCaesar(-1, txt);
    saveFile("texts.txt", txt);

    QSet<QString> dict = loadDict(loadFile("txt/dict.txt"));

    txt = loadFile("txt/F1_ciph_ces.txt");
    txt = decryptCaesar(dict, txt);
    saveFile("f1_decrypt.txt", txt);

    /*
    ushort table[33] = {
        L'а',
        L'б',
        L'в',
        L'г',
        L'д',
        L'е',
        L'ж',
        L'з',
        L'и',
        L'й',
        L'к',
        L'л',
        L'м',
        L'н',
        L'о',
        L'п',
        L'р',
        L'с',
        L'т',
        L'у',
        L'ф',
        L'х',
        L'ц',
        L'ч',
        L'ш',
        L'щ',
        L'ъ',
        L'ы',
        L'ь',
        L'э',
        L'ю',
        L'я',
    };
    */

    ushort table[33] = {
        L'о',
        L'г',
        L'в',
        L'б',
        L'д',
        L'е',
        L'ж',
        L'з',
        L'и',
        L'й',
        L'к',
        L'л',
        L'н',
        L'м',
        L'а',
        L'п',
        L'р',
        L'с',
        L'т',
        L'у',
        L'ф',
        L'х',
        L'ы',
        L'ч',
        L'ш',
        L'щ',
        L'ъ',
        L'ц',
        L'ь',
        L'э',
        L'ю',
        L'я',
    };

    txt = loadFile("txt/text.txt");
    txt = encryptCiph(table, txt);
    saveFile("textciph.txt", txt);

    txt = loadFile("txt/long_F1_ciph.txt");
    txt = decryptCiph(txt);
    saveFile("long_f1_decrypt.txt", txt);
}

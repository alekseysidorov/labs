#include <QString>
#include <QFile>
#include <QTextStream>
#include <QSet>
#include <QDebug>

#include <map>

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

typedef QMap<QString, int> WordsFrequencies;

QStringList loadDict(QString str)
{
    QMap<QString, int> dict;
    QTextStream in(&str);
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
        if (!word.isEmpty())
            dict[word]++;
    }

    QList<QPair<int, QString>> words;
    for (auto it = dict.begin(); it != dict.end(); ++it) {
        words.append(qMakePair(it.value(), it.key()));
    }
    std::sort(words.begin(), words.end());

    QStringList strs;
    for (auto w : words)
        strs.append(w.second);
    std::reverse(strs.begin(), strs.end());
    return strs;
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

QString decryptCaesar(const QStringList &dict, QString str)
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

QString encryptCiph(QChar *dict, const QString &s)
{
    QString out;
    for (int i = 0; i < s.size(); ++i) {
        QChar ch = s[i];
        if (ch >= L'а' && ch <= L'я') {
            ushort j = ch.unicode() - L'а';
            ch = dict[j];
        }
        out.append(ch);
    }

    return out;
}

void swapSymbol(QChar *table, QChar encrypted, QChar origin)
{
    int e = 0;
    for (int i = 0; i < 32; ++i) {
        if (table[i] == origin) {
            e = i; break;
        }
    }
    std::swap(table[encrypted.unicode() - L'а'], table[e]);
}

QString decryptCiph(QString ciph)
{
    QString s = loadFile("txt/book.txt").toLower();
    Frequencies dictFreqs = getFrequencies(s);
    Frequencies ciphFreqs = getFrequencies(ciph);

    // частотный анализ какого-то большого текста
    qDebug() << "dict frequencies: ";
    for (Frequency f : dictFreqs)
        qDebug() << QString(f.symbol) << ": " << f.frequency;
    qDebug() << "\n";

    // частотный анализ шифрованного текста
    qDebug() << "ciph frequencies: ";
    for (Frequency f : ciphFreqs)
        qDebug() << QString(f.symbol) << ": " << f.frequency;

    /// с автоматическим выводом таблицы дешифровки проблемы, поэтому ее нужно ручками добивать
    QChar table[33] = {
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

    ciph = encryptCiph(table, ciph);
    return ciph;
}

int main(int, char **)
{
    QString txt = loadFile("txt/text.txt");
    txt = encryptCaesar(-1, txt);
    saveFile("texts.txt", txt);

    QStringList dict = loadDict(loadFile("txt/dict.txt"));

    txt = loadFile("txt/F1_ciph_ces.txt");
    txt = decryptCaesar(dict, txt);
    saveFile("f1_decrypt.txt", txt);

    QChar table[33] = {
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

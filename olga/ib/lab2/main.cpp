#include <QString>
#include <QFile>
#include <QTextStream>
#include <QDebug>
#include <QBitArray>

typedef QVector<int32_t> IntVector;

QByteArray loadFile(const QString &name)
{
    QFile f(name);
    f.open(QFile::ReadOnly|QFile::Text);
    return f.readAll();
}

void saveFile(const QString &name, const QByteArray &data)
{
    QFile f(name);
    f.open(QFile::WriteOnly|QFile::Text);
    f.write(data);
}

IntVector loadMatrix(const QString &fileName)
{
    QByteArray data = loadFile(fileName);
    IntVector matrix;
    QTextStream in(&data);
    while (!in.atEnd()) {
        int32_t i;
        in >> i;
        matrix.push_back(i - 1);
    }
    return matrix;
}

QBitArray getBits(const QByteArray &bytes)
{
    QBitArray bits(bytes.count()*8);
    for(int i = 0; i < bytes.count(); ++i)
        for(int b = 0; b < 8; ++b)
            bits.setBit(i * 8 + b, bytes.at(i) & (1 << b));
    return bits;
}

QByteArray getBytes(const QBitArray &bits)
{
    QByteArray out;
    for (int i = 0; i < bits.count() / 8; ++i) {
        char c = 0;
        for (int j = 0; j < 8; ++j) {
            c |= bits[8 * i + j] << j;
        }
        out.append(c);
    }
    return out;
}

///
/// Переставляем биты в массиве bits в соответствии с матрицей перестановки matrix
///
QBitArray makePermutation(IntVector matrix, const QBitArray &bits)
{
    QBitArray out = bits;
    for (int i = 0; i < out.size(); ++i) {
        out[i] = bits[matrix[i]];
    }
    return out;
}

/// Циклический сдвиг битов на value элементов вправо
QBitArray shiftKey(const QBitArray &bits, int value)
{
    QBitArray head(value);
    for (int i = 0; i < value; ++i)
        head[i] = bits[i];

    QBitArray out(bits.size());
    int i = 0;
    for (; i < bits.size() - value; ++i) {
        out[i] = bits[i + value];
    }
    for (; i < bits.size(); ++i) {
        out[i] = head[i - bits.size() + value];
    }
    return out;
}

/// Подмассив битового массива
QBitArray subArray(const QBitArray &bits, int from, int size)
{
    QBitArray s(size);
    for (int i = 0; i < size; ++i)
        s[i] = bits[from + i];
    return s;
}

/// TODO
QBitArray generateShortKey(const QByteArray &key, int iteration)
{
    /// Заполняем таблицу сдвигов для всех итераций
    int shift[16];
    for (int i = 0; i < 16; ++i)
    {
        shift[i] = 2;
    }
    shift[0] = 1;
    shift[1] = 1;
    shift[8] = 1;
    shift[15] = 1;

    IntVector g = loadMatrix("txt/g.txt");
    QBitArray shortKey(56);
    QBitArray bitKey = getBits(key);
    for (int i = 0; i < shortKey.size(); ++i)
        shortKey[i] = bitKey[g[i]];

    /// левая и правая половинки
    QBitArray leftKey(28);
    QBitArray rightKey(28);
    for (int i = 0; i < 28; ++i) {
        leftKey[i] = shortKey[i];
        rightKey[i] = shortKey[i + 28];
    }

    /// сдвиги по табличке сдвигов
    for (int i = 0; i < iteration; ++i) {
        leftKey = shiftKey(leftKey, shift[i]);
        rightKey = shiftKey(rightKey, shift[i]);
    }

    /// склеивание назад
    for (int i = 0; i < 28; ++i) {
        shortKey[i] = leftKey[i];
        shortKey[i + 28] = rightKey[i];
    }

    IntVector kp = loadMatrix("txt/ip.txt");

    QBitArray tmp(48);
    for (int i = 0; i < 48; ++i)
    {
        tmp[i] = shortKey[kp[i]];
    }
    return tmp;
}

QBitArray f(QBitArray right, QBitArray shortKey)
{
    IntVector e = loadMatrix("txt/ext.txt");

    /// результат расширения E(R(i-1))
    QBitArray eRight(48);
    for (int i = 0; i < 48; ++i) {
        eRight[i] = right[e[i]];
    }

    /// сложение по модулю два с ключем K(i)
    eRight = eRight ^ shortKey;

    QBitArray b[8] = {
        subArray(eRight, 0, 6),
        subArray(eRight, 6, 6),
        subArray(eRight, 12, 6),
        subArray(eRight, 18, 6),
        subArray(eRight, 24, 6),
        subArray(eRight, 30, 6),
        subArray(eRight, 36, 6),
        subArray(eRight, 42, 6),
    };

    QBitArray result(32);
    for (int j = 0; j < 8; ++j) {
        IntVector s = loadMatrix(QString("txt/s%1.txt").arg(j + 1));

        int row = (b[j][1] << 1) | b[j][6];
        int column = (b[j][2] << 3) | (b[j][3] << 2) | (b[j][4] << 2) | (b[j][5]);
        int i = 16 * row + column;

        int o = s[i];
        for (int k = 0; k < 4; ++k) {
            result[j * 4 + k] = ((o << k) & 1);
        }
    }

    IntVector p2 = loadMatrix("txt/p2.txt");
    result = makePermutation(p2, result);
    return result;
}

QBitArray encryptBlock(QBitArray block, QByteArray key)
{
    /// левая и правая половинки
    QBitArray l(32);
    QBitArray r(32);
    for (int i = 0; i < 32; ++i) {
        l[i] = block[i];
        r[i] = block[i + 32];
    }

    for (int i = 1; i < 16; ++i) {
        QBitArray tmp = l;
        QBitArray shortKey = generateShortKey(key, i);
        l = r;
        r = tmp ^ f(r, shortKey);
    }

    QBitArray result(64);
    for (int i = 0; i < 32; ++i) {
        result[i] = l[i];
        result[i + 32] = r[i];
    }
    return result;
}

QByteArray encrypt(QByteArray array, QByteArray key)
{
    IntVector p = loadMatrix("txt/p.txt");
    IntVector ip = loadMatrix("txt/ip.txt");

    QByteArray out;
    for (int b = 0; b < array.size() / 8; ++b) {
        QByteArray block;
        for (int i = 0; i < 8; ++i) {
            block.append(array[8 * b + i]);
        }

        QBitArray bits = getBits(block);
        bits = makePermutation(p, bits);
        bits = encryptBlock(bits, key);
        bits = makePermutation(ip, bits);
        out += getBytes(bits);
    }
    return out;
}

int main(int, char **)
{
    QByteArray txt = loadFile("txt/text.txt");

    txt = encrypt(txt, "12345678");
    saveFile("text_encrypted.txt", txt);
}

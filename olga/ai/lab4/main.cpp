#include <iostream>
#include <fstream>
#include <cmath>
#include <limits>
#include <cstdlib>
#include <QList>
#include <vector>
#include <ctime>

// своя функция, вот её нужно подменить виндовой

#include <stdio.h>
#include <termios.h>
#include <unistd.h>

int my_getchar()
{
    struct termios oldt,
            newt;
    int ch;
    tcgetattr( STDIN_FILENO, &oldt );
    newt = oldt;
    newt.c_lflag &= ~( ICANON | ECHO );
    tcsetattr( STDIN_FILENO, TCSANOW, &newt );
    ch = getchar();
    tcsetattr( STDIN_FILENO, TCSANOW, &oldt );
    return ch;
}

struct question
{
    std::string text;
    int num;
};

struct answer
{
    char ch;
    int time;
};

// Загружалка вопросов из csv файла, в первом столбце вопрос, во втором y или n в зависимости от того, как на него отвечать надо
QList<question> load(std::string path)
{
    std::ifstream in(path);
    std::string line;
    QList<question> questions;
    int num = 0;
    while (std::getline(in, line)) {
        question q;
        q.text = line;
        q.num = num;
        num += 1;
        questions.push_back(q);
    }
    return questions;
}

bool is_answer(char ch)
{
    return (ch == 'y' || ch == 'n');
}

int main()
{
    setlocale(LC_ALL, "ru");
    std::srand(std::time(NULL));

    std::cout << "Здравствуйте, придумайте себе id" << std::endl;
    std::string name;
    std::cin >> name;
    // непонятный хак
    my_getchar();

    std::cout << "Отвечать на вопросы нужно буквами y или n." << std::endl
              << "Готовы ли вы приступить к тестированию (n/y)?" << std::endl;

    char ch;
    ch = my_getchar(); // увы, но getch использовать я не могу.
    if (ch != 'y')
        return 0;

    QList<question> questions = load("csv/questions.csv");
    std::vector<answer> atime; // время ответов на каждый из вопросов
    atime.resize(questions.size());

    while (!questions.empty()) {
        std::cout << "Нажмите любую клавишу для продолжения:" << std::endl;
        ch = my_getchar();
        std::cout << std::endl;

        int i = std::rand() % questions.size();
        question q = questions[i];

        std::cout << q.text << std::endl;
        int t = std::clock();
        ch = my_getchar();
        while (!is_answer(ch)) {
            ch = my_getchar();
        }
        int d = std::clock() - t;
        atime[q.num].time = d;
        atime[q.num].ch = ch;

        // удаляем вопрос из списка вопросов
        questions.removeAt(i);
    }

    std::ofstream fout("csv/" + name + ".csv");
    for (size_t i = 0; i < atime.size(); ++i) {
        fout << i << ";" << atime[i].ch << ";" << atime[i].time << std::endl;
    }
    return 0;
}

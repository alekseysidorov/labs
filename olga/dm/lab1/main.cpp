#include <iostream>
#include <string>
#include <map>
#include <set>

struct transition {
    int from;
    int to;
};

bool task1() {
    std::string word;
    size_t n, m, k;

    std::cin >> word >> n >> m >> k;

    std::set<int> states;
    states.insert(1);
    for (size_t i = 0; i < k; ++i) {
        int s;
        std::cin >> s;
        states.insert(s);
    }

    std::map<char, transition> trs;
    for (size_t i = 0; i < m; ++i) {
        transition tr; char c;
        std::cin >> tr.from >> tr.to >> c;
        trs[c] = tr;
    }

    int state = 1;
    for (size_t i = 0; i < word.size(); ++i) {
        auto t = trs.find(word[i]);
        if (t == trs.end()) {
            return false;
        }
        if (t->second.from != state) {
            return false;
        }
        if (states.find(t->second.to) == states.end()) {
            return false;
        }
        state = t->second.to;
    }
    return true;
}

bool task2()
{
    std::string word;
    size_t n, m, k;

    std::cin >> word >> n >> m >> k;

    std::set<int> states;
    states.insert(1);
    for (size_t i = 0; i < k; ++i) {
        int s;
        std::cin >> s;
        states.insert(s);
    }

    std::multimap<char, transition> trs;
    for (size_t i = 0; i < m; ++i) {
        transition tr; char c;
        std::cin >> tr.from >> tr.to >> c;
        trs.insert(std::make_pair(c, tr));
    }

    std::set<int> first;
    first.insert(1);
    for (size_t i = 0; i < word.size(); ++i) {
        std::set<int> second;
        for (auto it = trs.find(word[i]); it != trs.end(); ++it) {
            for (auto j : first) {
                if (it->second.from == j)
                    second.insert(it->second.to);
            }
        }
        first = second;
    }
    return !first.empty();
}

bool task3()
{
    size_t n, m, k;

    std::cin >> n >> m >> k;

    std::set<int> states;
    states.insert(1);
    for (size_t i = 0; i < k; ++i) {
        int s;
        std::cin >> s;
        states.insert(s);
    }

    std::map<char, transition> trs;
    for (size_t i = 0; i < m; ++i) {
        transition tr; char c;
        std::cin >> tr.from >> tr.to >> c;
        trs[c] = tr;
    }

    while (1) {
	trs
    }
}

int main(int, char **)
{
    if (task2()) {
        std::cout << "Accepts" << std::endl;
    } else {
        std::cout << "Rejects" << std::endl;
    }
}

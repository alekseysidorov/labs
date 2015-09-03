#include <iostream>
#include <vector>

/// Советую почитать эту ссылку.
///
/// \link http://e-maxx.ru/algo/strong_connected_components
///
/// P.S.
/// Тут куча русского текста в коде, на винде может глючить.
/// Когда сдавать пойдешь, лучше поставить таки линукс

typedef std::vector<std::vector<size_t> > graph_t;


/// Обход в глубину, при этом в out мы запоминаем
/// порядок выхода из вершины.
void dfs(const graph_t &edges, std::vector<size_t> &out, std::vector<bool> &visited, size_t node)
{
    visited[node] = true;

    for (size_t i = 0; i < edges[node].size(); ++i) {
        size_t node2 = edges[node][i];
        if (!visited[node2])
            dfs(edges, out, visited, node2);
    }
    out.push_back(node);
}

/// Обход в глубину, при этом в order мы запоминаем
/// порядок входа в вершину.
void dfs2(const graph_t &edges, std::vector<size_t> &in, std::vector<bool> &visited, size_t node)
{
    visited[node] = true;

    in.push_back(node);
    for (size_t i = 0; i < edges[node].size(); ++i) {
        size_t node2 = edges[node][i];
        if (!visited[node2])
            dfs2(edges, in, visited, node2);
    }
}

/// Печатаем компоненту связности и заодно очищаем её.
void print(std::vector<size_t> &component)
{
    for (size_t i = 0; i < component.size(); ++i) {
        std::cout << "  Вершина номер: " << (component[i] + 1) << std::endl;
    }
}

int main()
{
    size_t n, m;
    std::cin >> n >> m;

    graph_t edges; graph_t edges_t;

    /// Заполняем одновременно обычный граф edges и его транспонированную копию edges_t
    edges.resize(n);
    edges_t.resize(n);
    for (size_t i = 0; i < m; ++i) {
        size_t a, b;
        std::cin >> a >> b;

        a--;b--;

        edges[a].push_back(b);
        edges_t[b].push_back(a);
    }

    std::vector<size_t> out;

    /// Прямой поиск в глубину, на выходе order - порядок обхода.
    std::vector<bool> visited;
    visited.assign(n, false);
    for (size_t i = 0; i < n; ++i)
        if (!visited[i])
            dfs(edges, out, visited, i);

    /// Обратный проход, вывод компонент связности
    visited.assign(n, false);
    const size_t t = out.size();
    for (size_t i = 0; i < t; ++i) {
        int v = out[t - i -1];
        if (!visited[v]) {
            /// запускаем поиск в глубину с запоминанием порядка входа в вершины
            /// это и будет наша компонента сильной связности
            std::vector<size_t> component;
            dfs2(edges_t, component, visited, v);
            std::cout << "Сильная компонента связности номер: " << (i + 1) <<  std::endl;
            print(component);
        }
    }

    return 0;
}


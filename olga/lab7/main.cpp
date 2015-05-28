#include <iostream>
#include <vector>

typedef std::vector<std::vector<size_t> > graph_t;


void dfs(const graph_t &edges, std::vector<size_t> &order, std::vector<bool> &visited, size_t node)
{
    visited[node] = true;
    for (size_t i = 0; i < edges[node].size(); ++i) {
        size_t node2 = edges[node][i];
        if (!visited[node2])
            return dfs(edges, order, visited, node2);
    }

    order.push_back(node);
}

void dfs2(const graph_t &edges, std::vector<size_t> &order, std::vector<bool> &visited, size_t node)
{
    order.push_back(node);

    visited[node] = true;
    for (size_t i = 0; i < edges[node].size(); ++i) {
        size_t node2 = edges[node][i];
        if (!visited[node2])
            return dfs(edges, order, visited, node2);
    }
}

void print(std::vector<size_t> &component)
{
    for (size_t i = 0; i < component.size(); ++i) {
        std::cout << "  Вершина номер: " << component[i] << std::endl;
    }

    component.clear();
}

int main()
{
    size_t n, m;
    std::cin >> n >> m;

    graph_t edges; graph_t edges_t;

    edges.resize(n);
    edges_t.resize(n);
    for (size_t i = 0; i < m; ++i) {
        size_t a, b;
        std::cin >> a >> b;

        edges[a].push_back(b);
        edges_t[b].push_back(a);
    }

    std::vector<size_t> order, component;
    std::vector<bool> visited;

    /// Прямой поиск в глубину, на выходе order - порядок обхода.
    visited.assign(n, false);
    for (size_t i = 0; i < n; ++i)
        if (!visited[i])
            dfs(edges, order, visited, i);

    visited.assign(n, false);
    /// Обратный проход, вывод компонент связности
    for (size_t i = 0; i < n; ++i) {
        int v = order[n-1-i];
        if (!visited[v]) {
            dfs2(edges_t, component, visited, v);
            std::cout << "Сильная компонента связности номер: " << (i + 1) <<  std::endl;
            print(component);
        }
    }

    return 0;
}


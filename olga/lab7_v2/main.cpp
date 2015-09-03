#include <iostream>
#include <vector>

std::vector<std::vector<int> > g, gr;
std::vector<char> used;
std::vector<int> order, component;

void dfs1 (int v) {
    used[v] = true;
    for (size_t i=0; i<g[v].size(); ++i)
        if (!used[ g[v][i] ])
            dfs1 (g[v][i]);
    order.push_back (v);
}

void dfs2 (int v) {
    used[v] = true;
    component.push_back (v);
    for (size_t i=0; i<gr[v].size(); ++i)
        if (!used[ gr[v][i] ])
            dfs2 (gr[v][i]);
}

/// Печатаем компоненту связности и заодно очищаем её.
void print(std::vector<int> &component)
{
    for (size_t i = 0; i < component.size(); ++i) {
        std::cout << "  Вершина номер: " << (component[i] + 1) << std::endl;
    }
}

int main() {
    size_t n, m;
    std::cin >> n >> m;

    g.resize(n);
    gr.resize(n);
    /// Заполняем одновременно обычный граф edges и его транспонированную копию edges_t
    for (size_t i = 0; i < m; ++i) {
        size_t a, b;
        std::cin >> a >> b;

        a--;b--;

        g[a].push_back(b);
        gr[b].push_back(a);
    }

    used.assign(n, false);
    for (size_t i=0; i<n; ++i)
        if (!used[i])
            dfs1 (i);
    used.assign(n, false);
    for (size_t i=0; i<n; ++i) {
        int v = order[n-1-i];
        if (!used[v]) {
            dfs2(v);
            std::cout << "Сильная компонента связности номер: " << (i + 1) <<  std::endl;
            print(component);
            component.clear();
        }
    }
}

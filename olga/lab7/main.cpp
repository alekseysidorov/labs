#include <iostream>
#include <vector>

typedef std::vector<std::vector<size_t> > graph;

graph edges;
graph edges_t;
size_t c_num = 1;

std::vector<size_t> tout;

void dfs(std::vector<bool> &visited, size_t node)
{
    visited[node] = true;
    for (size_t i = 0; i < edges[node].size(); ++i) {
        size_t node2 = edges[node][i];
        if (!visited[node2])
            return dfs(visited, node2);
    }

    tout.push_back(node);
}

void dfs_print(std::vector<bool> &visited, size_t node)
{
    std::cout << "Вершина: " << node << std::endl;
    
    visited[node] = true;
    for (size_t i = 0; i < edges[node].size(); ++i) {
        size_t node2 = edges[node][i];
        if (!visited[node2])
            return dfs_print(visited, node2);
    }
}

void dfs_t(std::vector<bool> &visited, size_t node)
{
    visited[node] = true;
    for (size_t i = 0; i < edges_t[node].size(); ++i) {
        size_t node2 = edges_t[node][i];
        if (!visited[node2])
            return dfs_t(visited, node2);
    }

    std::cout << "Сильная компонента связности номер: " << c_num <<  std::endl;

    std::vector<bool> v1(edges.size(), false);
    dfs_print(v1, node);
}

void scc()
{
    std::vector<bool> v1(edges.size(), false);
    for (size_t i = 0; i < edges.size(); ++i)
        dfs(v1, i);

    std::vector<bool> v2(edges_t.size(), false);
    for (int i = tout.size() - 1; i >= 0; --i) {
        size_t node = tout[i];
        if (!v2[node]) {
            dfs_t(v2, node);
            ++c_num;
        }
    }
}

int main()
{
    size_t n, m;
    std::cin >> n >> m;

    edges.resize(n);
    edges_t.resize(n);
    for (size_t i = 0; i < m; ++i) {
        size_t from, to;
        std::cin >> from >> to;

        edges[from].push_back(to);
        edges_t[to].push_back(from);
    }

    scc();

    return 0;
}


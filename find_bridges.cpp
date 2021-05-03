#include <string>
#include <vector>
#include <iostream>
#include <algorithm>

class Graph {
public:
    int n_;
    bool is_not_direct_ = true;
    std::vector <std::vector<size_t>> edge;

    Graph(int n, bool is_not_direct) {
        is_not_direct_ = is_not_direct;
        n_ = n;
        edge.resize(n);
    }
    void AddEdge(int a, int b) {
        edge[a].push_back(b);
        if (is_not_direct_)
            edge[b].push_back(a);
    }
};



void dfs_make_or(const Graph& G, std::vector<size_t>& v,
    size_t now,
    size_t last,
    Graph& or_g,
    std::vector<size_t>& order) {
    v[now] = 1;
    for (size_t neig : G.edge[now]) {
        if (v[neig] == 0) {
            or_g.AddEdge(neig, now);
            dfs_make_or(G, v, neig, now, or_g, order);
        }
        else if (v[neig] != 0 && neig != last) {
            or_g.AddEdge(neig, now);
            or_g.AddEdge(now, neig);
        }
    }
    order.push_back(now);
    v[now] = 2;
}

void dfs_color(const Graph& G, std::vector<size_t>& coloring, size_t color, size_t now) {
    coloring[now] = color;
    for (size_t neig : G.edge[now]) {
        if (coloring[neig] == 0) {
            dfs_color(G, coloring, color, neig);
        }
    }
}

int main() {
    size_t n, m;
    std::cin >> n >> m;
    Graph g(n + 1, true);
    std::vector<std::pair<size_t, size_t>> edges;
    size_t a, b;
    for (size_t i = 0; i < m; ++i) {
        std::cin >> a >> b;
        g.AddEdge(a, b);
        edges.push_back({ a, b });
    }

    std::vector<size_t> visited(n + 1);
    std::vector<size_t> order;
    Graph or_g(n + 1, false);
    for (size_t i = 1; i <= n; ++i) {
        if (visited[i] == 0) {
            dfs_make_or(g, visited, i, 0, or_g, order);
        }
    }

    std::reverse(order.begin(), order.end());
    std::vector<size_t> coloring(n + 1);
    size_t color = 1;
    for (auto vertex : order) {
        if (coloring[vertex] == 0) {
            dfs_color(or_g, coloring, color, vertex);
            ++color;
        }
    }
    size_t bridge_count = 0;
    for (size_t i = 0; i < edges.size(); ++i) {
        if (coloring[edges[i].first] != coloring[edges[i].second]) {
            ++bridge_count;
        }
    }
    std::cout << bridge_count << '\n';
    for (size_t i = 0; i < edges.size(); ++i) {
        if (coloring[edges[i].first] != coloring[edges[i].second]) {
            std::cout << i + 1 << ' ';
        }
    }
    return 0;
}

#include <string>
#include <vector>
#include <iostream>
#include <algorithm>

template <class Container>
void PrintContainer(const Container& x) {
    for (auto i = x.begin(); i != x.end(); ++i) {
        std::cout << *i << ' ';
    }
    std::cout << std::endl;
}

class Graph {
public:
    int n_;
    bool is_not_direct_ = true;
    std::vector <std::vector<size_t>> edge;

    Graph(int n, bool is_not_direct) {
        is_not_direct_ = is_not_direct;
        n_ = n;
        edge.resize(n + 1);
    }
    void AddEdge(int a, int b) {
        edge[a].push_back(b);
        if (is_not_direct_)
            edge[b].push_back(a);
    }
    void CreatePath(int a, int b) {
        for (int i = a; i != b; ++i) {
            AddEdge(i, i + 1);
        }
    }
};

void dfs(const Graph& G, 
        std::vector<bool>& visited,
        std::vector<size_t>& tin,
        std::vector<size_t>& up,
        std::vector<size_t>& childs,
        std::vector<bool>& ap,
        size_t now,
        bool is_root,
        size_t time) {
    visited[now] = true;
    ++time;
    tin[now] = time;
    for (size_t neig : G.edge[now]) {
        if (!visited[neig]) {
            ++childs[now];
            dfs(G, visited, tin, up, childs, ap, neig, false, time);
            up[now] = std::min(up[now], up[neig]);
            if (up[neig] >= tin[now] && !is_root)
                ap[now] = true;
        }
        else {
            up[now] = std::min(up[now], tin[neig]);
        }
    }
}



void InputGraph(size_t edge_num, Graph& G) {
    size_t a, b;
    for (size_t i = 0; i < edge_num; ++i) {
        std::cin >> a >> b;
        G.AddEdge(a, b);
    }
}

int main() { 
    size_t n, m;
    std::cin >> n >> m;
    Graph G(n, true);
    InputGraph(m, G);
    std::vector<bool> visited(n + 1);
    std::vector<size_t> tin(n + 1);
    std::vector<size_t> up(n + 1, n + 2);
    std::vector<size_t> childs(n + 1);
    std::vector<bool> ap(n + 1);
    for (size_t now = 1; now <= n; ++now) {
        if (!visited[now]) {
            dfs(G, visited, tin, up, childs, ap, now, true, 0);
            if (childs[now] >= 2) {
                ap[now] = true;
            }
        }
    }
    size_t ap_num = 0;
    for (size_t i = 1; i <= n; ++i) {
        if (ap[i]) {
            ++ap_num;
        }
    }
    std::cout << ap_num << '\n';
    for (size_t i = 1; i <= n; ++i) {
        if (ap[i]) {
            std::cout << i << '\n';
        }
    }
    return 0;
}

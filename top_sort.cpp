#include <string>
#include <vector>
#include <iostream>
#include <algorithm>
//#include <windows.h>
//#include <shellapi.h>



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
        edge.resize(n);
    }
    void AddEdge(int a, int b) {
        edge[a].push_back(b);
        if (is_not_direct_)
            edge[b].push_back(a);
    }
};



void dfs(const Graph& G, std::vector<size_t>& v, size_t now, std::vector<size_t>& top_sorted_graph) {
    v[now] = 1;
    for (size_t neig : G.edge[now]) {
        if (v[neig] == 0) {
            dfs(G, v, neig, top_sorted_graph);
        }
        else if (v[neig] == 1) {
            top_sorted_graph.clear();
            top_sorted_graph.push_back(-1);
        }
    }
    v[now] = 2;
    top_sorted_graph.push_back(now);
}



void InputGraph(size_t edge_num, Graph& g) {
    size_t a, b;
    for (size_t i = 0; i < edge_num; ++i) {
        std::cin >> a >> b;
        g.AddEdge(a, b);
    }
}



int main() {
    size_t n, m;
    std::cin >> n >> m;
    Graph g(n + 1, false);
    InputGraph(m, g);
    std::vector<size_t> top_sorted_graph;
    std::vector<size_t> visited(n + 1);
    for (size_t i = 1; i <= n; ++i) {
        if (!visited[i]) {
            dfs(g, visited, i, top_sorted_graph);
        }
    }
    if (top_sorted_graph.front() != -1) {
        std::reverse(top_sorted_graph.begin(), top_sorted_graph.end());
        PrintContainer(top_sorted_graph);
    } else {
        std::cout << -1;
    }
    return 0;
}

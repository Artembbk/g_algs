#include <iostream>
#include <vector>

using namespace std;

void dfs(size_t now, const vector<vector<size_t>>& g, vector<bool>& v, vector<vector<size_t>>& components) {
    v[now] = true;
    components.back().push_back(now);
    for (size_t neig : g[now]) {
        if (!v[neig]) {
            dfs(neig, g, v, components);
        }
    }
}

int main() {
    size_t N, M;
    cin >> N >> M;
    vector<vector<size_t>> g(N + 1);
    size_t a,b;
    for (size_t i = 0; i < M; ++i) {
        cin >> a >> b;
        g[a].push_back(b);
        g[b].push_back(a);
    }
    vector<bool> v(N + 1);
    vector<vector<size_t>> components;
    for (size_t i = 1; i <= N; ++i) {
        if (!v[i]) {
            components.emplace_back();
            dfs(i, g, v, components);
        }
    }
    cout << components.size() << '\n';
    for (auto& component : components) {
        cout << component.size() << '\n';
        for (auto vertex : component) {
            cout << vertex << ' ';
        }
        cout << '\n';
    }
}

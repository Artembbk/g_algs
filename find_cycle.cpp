#include <iostream>
#include <vector>

using namespace std;

size_t changedColor(size_t color) {
    return 3 - color;
}

void dfs(size_t now, const vector<vector<size_t>>& g, vector<size_t>& v, vector<size_t>& cycle, size_t last) {
    v[now] = 1;
    for (size_t neig : g[now]) {
        if (v[neig] == 0) {
            dfs(neig, g, v, cycle, now);
            if (!cycle.empty()) {
                if (cycle.back() != 0) {
                    cycle.push_back(neig);
                    if (now == cycle[0]) {
                        cycle.push_back(0);
                    }
                }
                return;
            }
        } else if (v[neig] == 1 && neig != last) {
            cycle.push_back(neig);
            return;
        }
    }
    v[now] = 2;
}

int main() {
    size_t N;
    cin >> N;
    vector<vector<size_t>> g(N + 1);
    size_t e;
    vector<size_t> v(N + 1);
    for (size_t i = 1; i <= N; ++i) {
        for (size_t j = 1; j <= N; ++j) {
            cin >> e;
            if (e) {
                g[i].push_back(j);
            }
            
        }
    }
    vector<size_t> cycle;
    for (size_t i = 1; i <= N; ++i) {
        if (cycle.empty()) {
            dfs(i, g, v, cycle, 0);
        }
    }
    if (!cycle.empty()) {
        cout << "YES\n";
        cycle.pop_back();
        cout << cycle.size() << '\n';
        for (size_t i = 0; i < cycle.size(); ++i) {
            cout << cycle[i] << ' ';
        }
    } else {
        cout << "NO\n";
    }
}

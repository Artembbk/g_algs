#include <string>
#include <vector>
#include <iostream>
#include <algorithm>
#include <queue>
#include <set>
#include <cmath>

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
};


int main() {
  size_t v_num;
  std::cin >> v_num;
  std::vector<std::vector<int>> d(v_num + 1, std::vector<int>(v_num + 1));
  for (size_t i = 1; i <= v_num; ++i) {
    for (size_t j = 1; j <= v_num; ++j) {
      int weight;
      std::cin >> weight;
      d[i][j] = weight;
    }
  }

  for (size_t k = 1; k <= v_num; ++k) {
    for (size_t from = 1; from <= v_num; ++from) {
      for (size_t to = 1; to <= v_num; ++to) {
        d[from][to] = std::min(d[from][to], (d[from][k] + d[k][to]));
      }
    }
  }
  int max_route = -1;
  for (size_t i = 1; i <= v_num; ++i) {
    for (size_t j = 1; j <= v_num; ++j) {
      max_route = std::max(d[i][j], max_route);
    }
  }
  std::cout << max_route;
  return 0;
}

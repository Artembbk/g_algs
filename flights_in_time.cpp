#include <string>
#include <vector>
#include <iostream>
#include <algorithm>
#include <queue>
#include <set>
#include <map>
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

struct Flight {
  size_t from, to;
  long start_time, end_time;
};

bool operator < (const Flight& f1, const Flight& f2) {
  return f1.end_time > f2.end_time;
}

int main() {
  const long inf = 1000000001;
  size_t v_num;
  std::cin >> v_num;
  size_t start_v, end_v;
  std::cin >> start_v >> end_v;
  size_t e_num;
  std::cin >> e_num;
  std::vector<long> d(v_num + 1, inf);
  
  std::vector<Flight> flights;
  for (size_t i = 1; i <= e_num; ++i) {
    size_t from, to;
    long start_time, end_time;
    std::cin >> from >> start_time >> to >> end_time;
    flights.push_back({ from, to, start_time, end_time });
  }
  std::sort(flights.begin(), flights.end());
  d[start_v] = 0;
  for (size_t k = 0; k <= v_num; ++k) {
    for (const auto& flight : flights) {
      if (d[flight.from] <= flight.start_time)
        d[flight.to] = std::min(d[flight.to], flight.end_time);
    }
  }
  
  std::cout << d[end_v];
  return 0;
}

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

class WeightedGraph {
public:
  int n_;
  bool is_not_direct_ = true;
  std::vector <std::vector<std::pair<size_t, size_t>>> edge;

  WeightedGraph(int n, bool is_not_direct) {
	is_not_direct_ = is_not_direct;
	n_ = n;
	edge.resize(n + 1);
  }
  void AddEdge(int a, int b, int weight) {
	edge[a].push_back({ b, weight });
	if (is_not_direct_)
	  edge[b].push_back({ a, weight });
  }
};

using Vertex = std::pair<size_t, size_t>;

struct VMinDist {
  size_t dist;
  size_t from;
};


int main() {
  size_t v_num, e_num;
  std::cin >> v_num >> e_num;
  WeightedGraph g(v_num, true);
  int max_weight = -1;
  for (size_t i = 1; i <= e_num; ++i) {
    int v1, v2, weight;
    std::cin >> v1 >> v2 >> weight;
    max_weight = std::max(max_weight, weight);
    g.AddEdge(v1, v2, weight);
  }
  size_t v_start, v_end;
  std::cin >> v_start >> v_end;
  const size_t maxDist = v_num * max_weight;
  std::vector<bool> visited(v_num + 1);
  std::vector<VMinDist> dist(v_num + 1, { maxDist, 0 });
  dist[v_start].dist = 0;
  std::priority_queue<Vertex, std::vector<Vertex>, std::greater<Vertex>> dist_queue;
  for (size_t i = 1; i <= v_num; ++i) {
	if (i != v_start) {
	  dist_queue.push({ maxDist, i });
	} else {
	  dist_queue.push({ 0, i });
	}
  }
  while (dist_queue.top().first != maxDist && !dist_queue.empty()) {
	size_t now = dist_queue.top().second;
	if (visited[now]) {
	  dist_queue.pop();
	  continue;
	}
	visited[now] = true;
	for (const auto& [neig, weight] : g.edge[dist_queue.top().second]) {
	  if (dist[now].dist + weight < dist[neig].dist) {
		dist[neig].dist = dist[now].dist + weight;
		dist[neig].from = now;
		dist_queue.push({ dist[neig].dist, neig });
	  }
	}
	dist_queue.pop();
  }
  if (dist[v_end].dist != maxDist) {
	std::cout << dist[v_end].dist;
  } else {
	std::cout << -1;
  }
  return 0;
}

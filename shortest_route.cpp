#include <string>
#include <vector>
#include <iostream>
#include <algorithm>
#include <queue>
#include <set>

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


void bfs(const Graph& g, std::vector<std::pair<size_t, size_t>>& min_distances, 
         std::vector<std::vector<size_t>>& vertexes_on_dist) {
  size_t min_distance = 0;
  size_t vert;
  while (!vertexes_on_dist[min_distance].empty()) {
	for (size_t now : vertexes_on_dist[min_distance]) {
	  for (size_t neig : g.edge[now]) {
		if (min_distances[neig].first == g.n_) {
		  min_distances[neig] = { min_distances[now].first + 1, now };
		  vertexes_on_dist[min_distances[neig].first].push_back( neig );
		}
	  }
	}
	++min_distance;
  }
}


int main() {
  size_t n;
  std::cin >> n;
  Graph g(n, true);
  bool is_edge;
  for (size_t i = 1; i <= n; ++i) {
	for (size_t j = 1; j <= n; ++j) {
	  std::cin >> is_edge;
	  if (is_edge && i > j) g.AddEdge(i, j);
	}
  }
  //g.toDot();
  size_t start, end;
  std::cin >> start >> end;
  std::vector<std::pair<size_t, size_t>> min_distances(n + 1, { n, 0 });
  min_distances[start] = { 0, 0 };
  std::vector<std::vector<size_t>> vertexes_on_dist(n + 1);
  vertexes_on_dist[0].push_back(start);
  bfs(g, min_distances, vertexes_on_dist);
  if (min_distances[end].first == n) {
	std::cout << -1;
  } else {
	std::vector<size_t> route;
	size_t cur = end;
	while (cur != 0) {
	  route.push_back(cur);
	  cur = min_distances[cur].second;
	}
	std::reverse(route.begin(), route.end());
	std::cout << min_distances[end].first << '\n';
	if (min_distances[end].first != 0) {
	  PrintContainer(route);
	}
	
  }
  
  return 0;
}

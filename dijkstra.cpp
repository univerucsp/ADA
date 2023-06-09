#include <algorithm>
#include <iostream>
#include <limits>
#include <queue>
#include <vector>
using namespace std;

class Graph {
private:
  int numNodes;
  vector<vector<pair<int, int>>> adjacencyList;

public:
  Graph(int n) : numNodes(n), adjacencyList(n) {}

  void addEdge(int u, int v, int weight) {
    adjacencyList[u].push_back(make_pair(v, weight));
    adjacencyList[v].push_back(
        make_pair(u, weight)); // Si el grafo es no dirigido
  }

  vector<int> dijkstra(int start) {
    vector<int> distance(
        numNodes, numeric_limits<int>::max()); // Distancias iniciales infinitas
    vector<int> parent(numNodes, -1);          // Padres iniciales -1
    vector<bool> visited(numNodes, false); // Nodos no visitados inicialmente

    // Cola de prioridad para seleccionar el nodo con la distancia mínima
    priority_queue<pair<int, int>, vector<pair<int, int>>,
                   greater<pair<int, int>>>
        pq;

    distance[start] = 0; // Distancia del nodo de inicio a sí mismo es 0
    pq.push(make_pair(0, start));

    while (!pq.empty()) {
      int currNode = pq.top().second;
      pq.pop();

      if (visited[currNode])
        continue;

      visited[currNode] = true;

      // Explorar los vecinos del nodo actual
      for (const auto &neighbor : adjacencyList[currNode]) {
        int nextNode = neighbor.first;
        int edgeWeight = neighbor.second;
        int newDistance = distance[currNode] + edgeWeight;

        if (newDistance < distance[nextNode]) {
          distance[nextNode] = newDistance;
          parent[nextNode] = currNode;
          pq.push(make_pair(newDistance, nextNode));
        }
      }
    }

    return parent;
  }

  vector<int> reconstructPath(vector<int> &parent, int end) {
    vector<int> path;
    int currNode = end;

    while (currNode != -1) {
      path.push_back(currNode);
      currNode = parent[currNode];
    }

    reverse(path.begin(), path.end());

    return path;
  }
};

int main() {
  int n, m; // n: número de nodos, m: número de aristas
  cin >> n >> m;

  Graph graph(n);

  for (int i = 0; i < m; i++) {
    int u, v, w; // Arista de u a v con peso w
    cin >> u >> v >> w;
    graph.addEdge(u, v, w);
  }

  int start, end; // Nodo de inicio y nodo de destino
  cin >> start >> end;

  vector<int> parent = graph.dijkstra(start);
  vector<int> shortestPath = graph.reconstructPath(parent, end);

  if (shortestPath.empty()) {
    cout << "No hay camino desde el nodo " << start << " al nodo " << end
         << endl;
  } else {
    cout << "Camino más corto: ";
    for (int node : shortestPath)
      cout << node << " ";
    cout << endl;
  }

  return 0;
}

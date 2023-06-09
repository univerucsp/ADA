#include <iostream>
#include <queue>
#include <vector>

using namespace std;

typedef pair<int, int> pii;

class Graph {
private:
  int numNodes;
  vector<vector<pii>> adjacencyList;

public:
  Graph(int n) : numNodes(n), adjacencyList(n) {}

  void addEdge(int u, int v, int weight) {
    adjacencyList[u].push_back(make_pair(v, weight));
    adjacencyList[v].push_back(
        make_pair(u, weight)); // Si el grafo es no dirigido
  }

  int primMST() {
    priority_queue<pii, vector<pii>, greater<pii>>
        pq; // Cola de prioridad para seleccionar la arista de menor peso
    vector<bool> visited(numNodes, false); // Nodos visitados
    int minCost = 0; // Costo total del árbol de expansión mínima

    // Iniciar desde el nodo 0
    pq.push(make_pair(0, 0)); // Peso, nodo

    while (!pq.empty()) {
      int currNode = pq.top().second;
      int currWeight = pq.top().first;
      pq.pop();

      if (visited[currNode])
        continue;

      visited[currNode] = true;
      minCost += currWeight;

      // Explorar los vecinos del nodo actual
      for (const auto &neighbor : adjacencyList[currNode]) {
        int nextNode = neighbor.first;
        int edgeWeight = neighbor.second;

        if (!visited[nextNode]) {
          pq.push(make_pair(edgeWeight, nextNode));
        }
      }
    }

    return minCost;
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

  int minCost = graph.primMST();

  cout << "Costo mínimo del árbol de expansión mínima: " << minCost << endl;

  return 0;
}

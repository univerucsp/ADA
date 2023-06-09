#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

// Estructura para representar una arista
struct Edge {
  int source;
  int destination;
  int weight;

  Edge(int src, int dest, int w) : source(src), destination(dest), weight(w) {}

  // Sobrecarga del operador de comparación para ordenar las aristas por peso
  // creciente
  bool operator<(const Edge &other) const { return weight < other.weight; }
};

// Clase para representar un grafo
class Graph {
private:
  int numNodes;
  vector<Edge> edges;

public:
  Graph(int n) : numNodes(n) {}

  void addEdge(int src, int dest, int weight) {
    edges.push_back(Edge(src, dest, weight));
  }

  vector<Edge> kruskalMST() {
    // Ordenar las aristas por peso creciente
    sort(edges.begin(), edges.end());

    vector<Edge> mst;             // MST resultante
    vector<int> parent(numNodes); // Almacenar los padres de cada nodo

    // Inicializar los padres de cada nodo como el propio nodo
    for (int i = 0; i < numNodes; i++) {
      parent[i] = i;
    }

    int edgesTaken = 0; // Contador de aristas tomadas

    for (const auto &edge : edges) {
      int srcParent = findParent(parent, edge.source);
      int destParent = findParent(parent, edge.destination);

      if (srcParent != destParent) {
        // Agregar la arista al MST
        mst.push_back(edge);
        edgesTaken++;

        // Unir los conjuntos de nodos
        parent[srcParent] = destParent;

        // Si ya se han tomado todas las aristas necesarias, salir del bucle
        if (edgesTaken == numNodes - 1)
          break;
      }
    }

    return mst;
  }

  int findParent(vector<int> &parent, int node) {
    if (parent[node] != node) {
      parent[node] = findParent(parent, parent[node]);
    }
    return parent[node];
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

  vector<Edge> mst = graph.kruskalMST();

  cout << "Aristas del MST:" << endl;
  for (const auto &edge : mst) {
    cout << edge.source << " - " << edge.destination << " : " << edge.weight
         << endl;
  }

  return 0;
}

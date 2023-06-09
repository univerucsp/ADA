#include <cmath>
#include <iostream>
#include <limits>
#include <vector>

using namespace std;

const int INF = numeric_limits<int>::max();

// Función que calcula la longitud del camino más corto desde el nodo i hasta el
// nodo 1, pasando exactamente una vez por cada nodo en el conjunto S.
int g(int i, int S, const vector<vector<int>> &dist,
      vector<vector<int>> &memo) {
  if (S == 0) {
    // Si S es el conjunto vacío, el camino más corto es la distancia directa
    // desde i hasta el nodo 1.
    return dist[i][0];
  }

  if (memo[i][S] != -1) {
    // Si el resultado ya está almacenado en la memoria, se devuelve.
    return memo[i][S];
  }

  int minCost = INF;

  for (int j = 0; j < dist.size(); j++) {
    if (j != i && (S & (1 << j))) {
      // Si el nodo j pertenece al conjunto S, se calcula el costo de ir de i a
      // j y luego de j al conjunto S - {j}.
      int cost = dist[i][j] + g(j, S & ~(1 << j), dist, memo);
      minCost = min(minCost, cost);
    }
  }

  // Se almacena el resultado en la memoria.
  memo[i][S] = minCost;

  return minCost;
}

int tsp(vector<vector<int>> &dist) {
  int n = dist.size();

  // Se crea la matriz de memorización.
  vector<vector<int>> memo(n, vector<int>(1 << n, -1));

  // Caso base: g(1, {}) = 0.
  memo[0][0] = 0;

  // Se calcula el valor de g(1, V - {1}).
  int minTourCost = g(0, (1 << n) - 1, dist, memo);

  return minTourCost;
}

int main() {
  vector<vector<int>> dist = {
      {0, 2, 9, 10}, {1, 0, 6, 4}, {15, 7, 0, 8}, {6, 3, 12, 0}};

  int minTourCost = tsp(dist);

  cout << "Longitud del circuito hamiltoniano minimal: " << minTourCost << endl;

  return 0;
}

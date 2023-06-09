#include <iostream>
#include <limits>
#include <vector>

#define INF std::numeric_limits<int>::max()

void floydWarshall(std::vector<std::vector<int>> &N) {
  int n = N.size();

  for (int k = 0; k < n; k++) {
    for (int i = 0; i < n; i++) {
      for (int j = 0; j < n; j++) {
        if (N[i][k] != INF && N[k][j] != INF && N[i][k] + N[k][j] < N[i][j]) {
          N[i][j] = N[i][k] + N[k][j];
        }
      }
    }
  }
}

int main() {
  std::vector<std::vector<int>> N = {{0, 17, 8, 16, 20},
                                     {INF, 0, 12, 6, 15},
                                     {INF, INF, 0, 12, 16},
                                     {INF, INF, INF, 0, 15},
                                     {INF, INF, INF, INF, 0}};

  floydWarshall(N);

  int n = N.size();
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      std::cout << N[i][j] << " ";
    }
    std::cout << std::endl;
  }

  return 0;
}

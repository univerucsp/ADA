#include <iostream>
#include <vector>

using namespace std;

int mochila(int capacidad, const vector<int> &pesos,
            const vector<int> &valores) {
  int n = pesos.size();

  vector<vector<int>> dp(n + 1, vector<int>(capacidad + 1, 0));

  for (int i = 1; i <= n; i++) {
    for (int j = 1; j <= capacidad; j++) {
      if (pesos[i - 1] <= j) {
        dp[i][j] =
            max(dp[i - 1][j], valores[i - 1] + dp[i - 1][j - pesos[i - 1]]);
      } else {
        dp[i][j] = dp[i - 1][j];
      }
    }
  }

  return dp[n][capacidad];
}

int main() {
  int capacidad;
  cout << "Ingrese la capacidad de la mochila: ";
  cin >> capacidad;

  int n;
  cout << "Ingrese el número de objetos: ";
  cin >> n;

  vector<int> pesos(n);
  vector<int> valores(n);

  cout << "Ingrese los pesos de los objetos: ";
  for (int i = 0; i < n; i++) {
    cin >> pesos[i];
  }

  cout << "Ingrese los valores de los objetos: ";
  for (int i = 0; i < n; i++) {
    cin >> valores[i];
  }

  int valorOptimo = mochila(capacidad, pesos, valores);

  cout << "El valor máximo que se puede obtener es: " << valorOptimo << endl;

  return 0;
}

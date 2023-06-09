#include <iostream>
#include <vector>

using namespace std;

bool precedeEnOrden(char u, char v) {
  // Definir la relación de orden Φ según los requerimientos del problema
  if (u == 'a' && v == 'b')
    return true;
  if (u == 'a' && v == 'c')
    return true;
  if (u == 'a' && v == 'd')
    return true;
  if (u == 'b' && v == 'c')
    return true;
  if (u == 'b' && v == 'd')
    return true;
  if (u == 'c' && v == 'd')
    return true;

  return false;
}

bool precedeEnOrdenDinamico(char u, char v) {
  vector<vector<bool>> dp(
      4,
      vector<bool>(
          4,
          false)); // Matriz de programación dinámica (4x4 para Σ = {a,b,c,d})

  // Inicializar la matriz para los casos base
  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 4; j++) {
      if (i == j)
        dp[i][j] = true; // Cualquier elemento precede a sí mismo
    }
  }

  // Calcular las entradas de la matriz utilizando programación dinámica
  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 4; j++) {
      if (i != j) {
        dp[i][j] = precedeEnOrden(
            'a' + i, 'a' + j); // Verificar si 'a'+i precede a 'a'+j
        for (int k = 0; k < 4; k++) {
          if (dp[i][j] && dp[j][k])
            dp[i][k] = true; // Si 'a'+i precede a 'a'+j y 'a'+j precede a
                             // 'a'+k, entonces 'a'+i precede a 'a'+k
        }
      }
    }
  }

  int uIndex = u - 'a';
  int vIndex = v - 'a';

  return dp[uIndex][vIndex];
}

int main() {
  char u, v;

  cout << "Ingrese el primer elemento (u): ";
  cin >> u;

  cout << "Ingrese el segundo elemento (v): ";
  cin >> v;

  bool precede = precedeEnOrdenDinamico(u, v);

  if (precede)
    cout << u << " precede a " << v << " en el orden Φ." << endl;
  else
    cout << u << " no precede a " << v << " en el orden Φ." << endl;

  return 0;
}

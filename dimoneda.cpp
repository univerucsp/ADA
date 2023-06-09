#include <iostream>
#include <vector>
#define INT_MAX 100
using namespace std;

vector<int> devolverVuelto(int monto, const vector<int> &denominaciones) {
  int n = denominaciones.size();

  vector<int> cantidadMonedas(
      monto + 1, INT_MAX); // Cantidad mínima de monedas para cada monto
  vector<int> ultimaMoneda(monto + 1,
                           -1); // Última moneda utilizada para cada monto

  cantidadMonedas[0] =
      0; // Caso base: no se necesita ninguna moneda para un monto de 0

  for (int i = 1; i <= monto; i++) {
    for (int j = 0; j < n; j++) {
      if (denominaciones[j] <= i &&
          cantidadMonedas[i - denominaciones[j]] + 1 < cantidadMonedas[i]) {
        cantidadMonedas[i] = cantidadMonedas[i - denominaciones[j]] + 1;
        ultimaMoneda[i] = j;
      }
    }
  }

  // Construir la solución (vuelto)
  vector<int> vuelto;
  int montoActual = monto;

  while (montoActual > 0) {
    int indiceMoneda = ultimaMoneda[montoActual];
    vuelto.push_back(denominaciones[indiceMoneda]);
    montoActual -= denominaciones[indiceMoneda];
  }

  return vuelto;
}

int main() {
  int monto;
  cout << "Ingrese el monto a devolver: ";
  cin >> monto;

  int numDenominaciones;
  cout << "Ingrese el número de denominaciones de monedas: ";
  cin >> numDenominaciones;

  vector<int> denominaciones(numDenominaciones);
  cout << "Ingrese las denominaciones de las monedas: ";
  for (int i = 0; i < numDenominaciones; i++) {
    cin >> denominaciones[i];
  }

  vector<int> vuelto = devolverVuelto(monto, denominaciones);

  cout << "El vuelto utilizando la menor cantidad de monedas es: ";
  for (int i = 0; i < vuelto.size(); i++) {
    cout << vuelto[i] << " ";
  }
  cout << endl;

  return 0;
}

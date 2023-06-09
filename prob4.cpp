#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;

vector<int> secuenciaCrecienteMaxima(vector<int> &nums) {
  int n = nums.size();

  // Caso base: cada elemento individual forma una secuencia creciente de
  // longitud 1
  vector<int> dp(n, 1);

  // Almacenar los índices de los elementos que forman parte de la secuencia
  // creciente máxima
  vector<int> indices(n, -1);
  int maxLen = 1; // Longitud de la secuencia creciente máxima
  int endIndex =
      0; // Índice del último elemento de la secuencia creciente máxima

  // Calcular las longitudes de las secuencias crecientes para cada elemento
  for (int i = 1; i < n; i++) {
    for (int j = 0; j < i; j++) {
      if (nums[i] > nums[j] && dp[i] < dp[j] + 1) {
        dp[i] = dp[j] + 1;
        indices[i] = j;

        // Actualizar la longitud máxima y el índice del último elemento de la
        // secuencia creciente máxima
        if (dp[i] > maxLen) {
          maxLen = dp[i];
          endIndex = i;
        }
      }
    }
  }

  // Reconstruir la secuencia creciente máxima
  vector<int> secuencia;
  int currentIndex = endIndex;
  while (currentIndex != -1) {
    secuencia.push_back(nums[currentIndex]);
    currentIndex = indices[currentIndex];
  }

  reverse(
      secuencia.begin(),
      secuencia.end()); // Invertir la secuencia para obtener el orden creciente

  return secuencia;
}

int main() {
  vector<int> nums = {11, 17, 5, 8, 6, 4, 7, 12, 3};

  vector<int> secuenciaMaxima = secuenciaCrecienteMaxima(nums);

  cout << "Secuencia creciente de máxima longitud: ";
  for (int num : secuenciaMaxima) {
    cout << num << " ";
  }
  cout << endl;

  return 0;
}

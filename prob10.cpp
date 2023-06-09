#include <algorithm>
#include <iostream>
#include <vector>

int maxResourceAllocation(const std::vector<std::vector<int>> &N, int n,
                          int r) {
  std::vector<std::vector<int>> dp(n + 1, std::vector<int>(r + 1, 0));

  for (int i = 1; i <= n; i++) {
    for (int j = 1; j <= r; j++) {
      dp[i][j] = dp[i][j - 1];
      for (int k = 1; k <= std::min(i, static_cast<int>(N.size()) - 1); k++) {
        int temp = dp[i - k][j - 1] + N[k][j];
        dp[i][j] = std::max(dp[i][j], temp);
      }
    }
  }

  return dp[n][r];
}

int main() {
  std::vector<std::vector<int>> N = {
      {0, 0, 0, 0}, {0, 5, 7, 4}, {0, 2, 3, 1}, {0, 4, 2, 5}};

  int n = 4;
  int r = 3;

  int result = maxResourceAllocation(N, n, r);
  std::cout << result << std::endl; // Salida: 16

  return 0;
}

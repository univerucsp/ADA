#include <iostream>
#include <string>
#include <vector>

bool checkParentheses(const std::string &x) {
  int n = x.size();
  std::vector<std::vector<bool>> dp(n + 1, std::vector<bool>(n + 1, false));

  for (int i = 1; i <= n; i++) {
    if (x[i - 1] == 'a') {
      dp[i][i] = true;
    }
  }

  for (int l = 2; l <= n; l++) {
    for (int i = 1; i <= n - l + 1; i++) {
      int j = i + l - 1;
      dp[i][j] = false;

      for (int k = i; k < j; k++) {
        if (dp[i][k] && dp[k + 1][j]) {
          if ((x[i - 1] == 'a' && x[k] == 'c') ||
              (x[i - 1] == 'c' && x[k] == 'a')) {
            dp[i][j] = true;
            break;
          }
        }
      }

      if ((x[i - 1] == 'a' && x[j - 1] == 'c') ||
          (x[i - 1] == 'c' && x[j - 1] == 'a')) {
        dp[i][j] = true;
      }
    }
  }

  return dp[1][n];
}

int main() {
  std::string x = "abcab";
  bool result = checkParentheses(x);
  std::cout << std::boolalpha;
  std::cout << result << std::endl; // Salida: true

  return 0;
}

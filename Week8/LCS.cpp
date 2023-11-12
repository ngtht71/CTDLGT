/**
Cho 2 dãy a gồm m phần tử, b gồm n phần tử.
Tìm độ dài dãy con chung dài nhất (LCS - Longest common subsequence)
của hai dãy a và b.
*/

#include <iostream>

using namespace std;

int LCS(string X, string Y) {
    int m = X.length();
    int n = Y.length();

    int dp[m+1][n+1];
    for (int i = 0; i <= m; i++) dp[i][0] = 0;
    for (int i = 0; i <= n; i++) dp[0][i] = 0;

    for (int i = 1; i <= m; i++) {
        for (int j = 1; j <= n; j++) {
            if (X[i] == Y[j]) dp[i][j] = dp[i-1][j-1] + 1;
            else dp[i][j] = max(dp[i][j-1], dp[i-1][j]);
        }
    }
    return dp[m][n];
}

int main() {
    string a, b;
    a = "ACGGA";
    b = "ACTG";
    // LCS: ACG
    cout << "Longest Common String " << a << " and " << b << " is: " << LCS(a, b);
    return 0;
}

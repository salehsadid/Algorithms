#include <iostream>
#include <vector>
#include <string>
#include <bits/stdc++.h>

using namespace std;

int lcs(string s1, string s2) {
    int m = s1.length();
    int n = s2.length();
    
    // Create DP table
    vector<vector<int>> dp(m + 1, vector<int>(n + 1, 0));
    
    // Fill the DP table
    for (int i = 1; i <= m; i++) {
        for (int j = 1; j <= n; j++) {
            if (s1[i - 1] == s2[j - 1]) {
                dp[i][j] = dp[i - 1][j - 1] + 1;
            } else {
                dp[i][j] = max(dp[i - 1][j], dp[i][j - 1]);
            }
        }
    }
    
    return dp[m][n];
}

string getLCS(string s1, string s2) {
    int m = s1.length();
    int n = s2.length();
    
    // Create DP table
    vector<vector<int>> dp(m + 1, vector<int>(n + 1, 0));
    
    // Fill the DP table
    for (int i = 1; i <= m; i++) {
        for (int j = 1; j <= n; j++) {
            if (s1[i - 1] == s2[j - 1]) {
                dp[i][j] = dp[i - 1][j - 1] + 1;
            } else {
                dp[i][j] = max(dp[i - 1][j], dp[i][j - 1]);
            }
        }
    }
    
    // Backtrack to find the LCS string
    string result = "";
    int i = m, j = n;
    
    while (i > 0 && j > 0) {
        if (s1[i - 1] == s2[j - 1]) {
            result = s1[i - 1] + result;
            i--;
            j--;
        } else if (dp[i - 1][j] > dp[i][j - 1]) {
            i--;
        } else {
            j--;
        }
    }
    
    return result;
}

int main() {
    
    string s1 = "AGGTAB";
    string s2 = "GXTXAYB";
    
    cout << "String 1: " << s1 << endl;
    cout << "String 2: " << s2 << endl;
    
    int length = lcs(s1, s2);
    cout << "Length of LCS: " << length << endl;
    
    string lcsString = getLCS(s1, s2);
    cout << "LCS: " << lcsString << endl;
    
    return 0;
}

#include <iostream>
#include <vector>
#include <string>
#include <bits/stdc++.h>

using namespace std;

int lcs3(string s1, string s2, string s3) {
    int m = s1.length();
    int n = s2.length();
    int o = s3.length();
    
    // Create 3D DP table
    vector<vector<vector<int>>> dp(m + 1, vector<vector<int>>(n + 1, vector<int>(o + 1, 0)));
    
    // Fill the DP table
    for (int i = 1; i <= m; i++) {
        for (int j = 1; j <= n; j++) {
            for (int k = 1; k <= o; k++) {
                if (s1[i - 1] == s2[j - 1] && s2[j - 1] == s3[k - 1]) {
                    dp[i][j][k] = dp[i - 1][j - 1][k - 1] + 1;
                } else {
                    dp[i][j][k] = max({dp[i - 1][j][k], dp[i][j - 1][k], dp[i][j][k - 1]});
                }
            }
        }
    }
    
    return dp[m][n][o];
}

string getLCS3(string s1, string s2, string s3) {
    int m = s1.length();
    int n = s2.length();
    int o = s3.length();
    
    // Create 3D DP table
    vector<vector<vector<int>>> dp(m + 1, vector<vector<int>>(n + 1, vector<int>(o + 1, 0)));
    
    // Fill the DP table
    for (int i = 1; i <= m; i++) {
        for (int j = 1; j <= n; j++) {
            for (int k = 1; k <= o; k++) {
                if (s1[i - 1] == s2[j - 1] && s2[j - 1] == s3[k - 1]) {
                    dp[i][j][k] = dp[i - 1][j - 1][k - 1] + 1;
                } else {
                    dp[i][j][k] = max({dp[i - 1][j][k], dp[i][j - 1][k], dp[i][j][k - 1]});
                }
            }
        }
    }
    
    // Backtrack to find the LCS string
    string result = "";
    int i = m, j = n, k = o;
    
    while (i > 0 && j > 0 && k > 0) {
        if (s1[i - 1] == s2[j - 1] && s2[j - 1] == s3[k - 1]) {
            result = s1[i - 1] + result;
            i--;
            j--;
            k--;
        } else {
            int maxVal = max({dp[i - 1][j][k], dp[i][j - 1][k], dp[i][j][k - 1]});
            
            if (dp[i - 1][j][k] == maxVal) {
                i--;
            } else if (dp[i][j - 1][k] == maxVal) {
                j--;
            } else {
                k--;
            }
        }
    }
    
    return result;
}

int main() {
    
    string s1 = "AGGT12";
    string s2 = "12TXAYB";
    string s3 = "12XBA";
    
    cout << "String 1: " << s1 << endl;
    cout << "String 2: " << s2 << endl;
    cout << "String 3: " << s3 << endl;
    
    int length = lcs3(s1, s2, s3);
    cout << "Length of LCS: " << length << endl;
    
    string lcsString = getLCS3(s1, s2, s3);
    cout << "LCS: " << lcsString << endl;
    
    return 0;
}

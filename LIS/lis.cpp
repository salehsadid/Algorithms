#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

// O(n^2) DP approach
int lisDP(vector<int>& arr) {
    int n = arr.size();
    vector<int> dp(n, 1);
    
    for (int i = 1; i < n; i++) {
        for (int j = 0; j < i; j++) {
            if (arr[j] < arr[i]) {
                dp[i] = max(dp[i], dp[j] + 1);
            }
        }
    }
    
    return *max_element(dp.begin(), dp.end());
}

// O(n^2) DP with subsequence reconstruction
vector<int> getLIS_DP(vector<int>& arr) {
    int n = arr.size();
    vector<int> dp(n, 1);
    vector<int> parent(n, -1);
    
    for (int i = 1; i < n; i++) {
        for (int j = 0; j < i; j++) {
            if (arr[j] < arr[i] && dp[j] + 1 > dp[i]) {
                dp[i] = dp[j] + 1;
                parent[i] = j;
            }
        }
    }
    
    // Find the index with maximum LIS length
    int maxLen = 0, maxIdx = 0;
    for (int i = 0; i < n; i++) {
        if (dp[i] > maxLen) {
            maxLen = dp[i];
            maxIdx = i;
        }
    }
    
    // Reconstruct the LIS
    vector<int> lis;
    int idx = maxIdx;
    while (idx != -1) {
        lis.push_back(arr[idx]);
        idx = parent[idx];
    }
    
    reverse(lis.begin(), lis.end());
    return lis;
}

// O(n log n) Binary Search approach
int lisBinarySearch(vector<int>& arr) {
    int n = arr.size();
    vector<int> tail;
    
    for (int i = 0; i < n; i++) {
        auto it = lower_bound(tail.begin(), tail.end(), arr[i]);
        
        if (it == tail.end()) {
            tail.push_back(arr[i]);
        } else {
            *it = arr[i];
        }
    }
    
    return tail.size();
}

// O(n log n) with subsequence reconstruction
vector<int> getLIS_BinarySearch(vector<int>& arr) {
    int n = arr.size();
    vector<int> tail;
    vector<int> tailIdx;
    vector<int> parent(n, -1);
    
    for (int i = 0; i < n; i++) {
        auto it = lower_bound(tail.begin(), tail.end(), arr[i]);
        int pos = it - tail.begin();
        
        if (it == tail.end()) {
            tail.push_back(arr[i]);
            tailIdx.push_back(i);
        } else {
            *it = arr[i];
            tailIdx[pos] = i;
        }
        
        if (pos > 0) {
            parent[i] = tailIdx[pos - 1];
        }
    }
    
    // Reconstruct the LIS
    vector<int> lis;
    int idx = tailIdx.back();
    while (idx != -1) {
        lis.push_back(arr[idx]);
        idx = parent[idx];
    }
    
    reverse(lis.begin(), lis.end());
    return lis;
}

int main() {
    
    vector<int> arr = {10, 9, 2, 5, 3, 7, 101, 18};
    
    cout << "Array: ";
    for (int x : arr) cout << x << " ";
    cout << endl;
    
    // Method 1: O(n^2) DP
    cout << "\nMethod 1 - O(n^2) DP:" << endl;
    cout << "LIS Length: " << lisDP(arr) << endl;
    
    vector<int> lis1 = getLIS_DP(arr);
    cout << "LIS: ";
    for (int x : lis1) cout << x << " ";
    cout << endl;
    
    // Method 2: O(n log n) Binary Search
    cout << "\nMethod 2 - O(n log n) Binary Search:" << endl;
    cout << "LIS Length: " << lisBinarySearch(arr) << endl;
    
    vector<int> lis2 = getLIS_BinarySearch(arr);
    cout << "LIS: ";
    for (int x : lis2) cout << x << " ";
    cout << endl;
    
    return 0;
}

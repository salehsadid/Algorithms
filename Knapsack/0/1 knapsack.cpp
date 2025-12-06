#include <iostream>
#include <vector>
using namespace std;

int knapsack(int capacity, vector<int>& weights, vector<int>& values, int n) {
    vector<vector<int>> dp(n + 1, vector<int>(capacity + 1, 0));
    for (int i = 1; i <= n; i++) {
        for (int w = 1; w <= capacity; w++) {
            if (weights[i - 1] <= w) {
                dp[i][w] = max(values[i - 1] + dp[i - 1][w - weights[i - 1]], dp[i - 1][w]);
            } else {
                dp[i][w] = dp[i - 1][w];
            }
        }
    }
    return dp[n][capacity];
}
vector<int> getSelectedItems(int capacity, vector<int>& weights, vector<int>& values, int n) {
    vector<vector<int>> dp(n + 1, vector<int>(capacity + 1, 0));
    for (int i = 1; i <= n; i++) {
        for (int w = 1; w <= capacity; w++) {
            if (weights[i - 1] <= w) {
                dp[i][w] = max(values[i - 1] + dp[i - 1][w - weights[i - 1]], dp[i - 1][w]);
            } else {
                dp[i][w] = dp[i - 1][w];
            }
        }
    }
    vector<int> selected;
    int w = capacity;
    
    for (int i = n; i > 0; i--) {
        if (dp[i][w] != dp[i - 1][w]) {
            selected.push_back(i - 1);
            w -= weights[i - 1];
        }
    }
    return selected;
}

int main() {
    
    int capacity = 50;
    vector<int> weights = {10, 20, 30};
    vector<int> values = {60, 100, 120};
    int n = weights.size();
    
    cout << "Items (value, weight):" << endl;
    for (int i = 0; i < n; i++) {
        cout << "Item " << i + 1 << ": (" << values[i] << ", " << weights[i] << ")" << endl;
    }
    
    cout << "\nKnapsack Capacity: " << capacity << endl;
    
    int maxValue = knapsack(capacity, weights, values, n);
    cout << "Maximum value: " << maxValue << endl;
    
    vector<int> selected = getSelectedItems(capacity, weights, values, n);
    cout << "\nSelected items: ";
    for (int i = selected.size() - 1; i >= 0; i--) {
        cout << selected[i] + 1 << " ";
    }
    cout << endl;
    
    return 0;
}

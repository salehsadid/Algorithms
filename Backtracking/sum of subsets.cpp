#include <iostream>
#include <vector>
using namespace std;

void sumOfSubsets(vector<int>& arr, vector<int>& subset, int index, int currentSum, int targetSum, int n) {
    // Base case: if target sum is achieved
    if (currentSum == targetSum) {
        cout << "{ ";
        for (int i = 0; i < subset.size(); i++) {
            cout << subset[i] << " ";
        }
        cout << "}" << endl;
        return;
    }
    
    // If all elements are processed or sum exceeds target
    if (index == n || currentSum > targetSum) {
        return;
    }
    
    // Include current element
    subset.push_back(arr[index]);
    sumOfSubsets(arr, subset, index + 1, currentSum + arr[index], targetSum, n);
    
    // Backtrack: exclude current element
    subset.pop_back();
    sumOfSubsets(arr, subset, index + 1, currentSum, targetSum, n);
}

int main() {
    int n, targetSum;
    
    cout << "Enter number of elements: ";
    cin >> n;
    
    vector<int> arr(n);
    cout << "Enter elements: ";
    for (int i = 0; i < n; i++) {
        cin >> arr[i];
    }
    
    cout << "Enter target sum: ";
    cin >> targetSum;
    
    vector<int> subset;
    cout << "\nSubsets with sum " << targetSum << ":" << endl;
    sumOfSubsets(arr, subset, 0, 0, targetSum, n);
    
    return 0;
}
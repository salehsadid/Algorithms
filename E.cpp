#include <iostream>
#include <iomanip>
#include <vector>
using namespace std;

const int INF = 1e9;

int main() {
    int n, k;
    cin >> n >> k;
    
    vector<vector<int>> dist(n + 1, vector<int>(n + 1, INF));
    
    for (int i = 1; i <= n; i++) {
        dist[i][i] = 0;
    }
    
    for (int i = 0; i < k; i++) {
        int a, b, l;
        cin >> a >> b >> l;
        dist[a][b] = min(dist[a][b], l);
    }
    
    // Floyd-Warshall algorithm
    for (int k = 1; k <= n; k++) {
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= n; j++) {
                if (dist[i][k] != INF && dist[k][j] != INF) {
                    dist[i][j] = min(dist[i][j], dist[i][k] + dist[k][j]);
                }
            }
        }
    }
    
    // Calculate average
    long long sum = 0;
    int count = 0;
    
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            if (i != j && dist[i][j] != INF) {
                sum += dist[i][j];
                count++;
            }
        }
    }
    
    if (count > 0) {
        double average = (double)sum / count;
        cout << fixed << setprecision(6) << average << endl;
    } else {
        cout << fixed << setprecision(6) << 0.0 << endl;
    }
    
    return 0;
}

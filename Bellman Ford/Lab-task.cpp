#include <bits/stdc++.h>
using namespace std;

#define INF 1e18

int main() {
    int n, m;
    cin >> n >> m;
    
    vector<tuple<int, int, long long>> edges;
    
    for (int i = 0; i < m; i++) {
        int a, b;
        long long c;
        cin >> a >> b >> c;
        edges.push_back({a, b, c});
    }
    
    // Bellman-Ford algorithm
    vector<long long> dist(n + 1, INF);
    vector<int> parent(n + 1, -1);
    
    // Initialize distance for node 1
    dist[1] = 0;
    
    int x = -1; // Node that is part of negative cycle
    
    // Relax edges n times (one extra time to detect negative cycle)
    for (int i = 0; i < n; i++) {
        x = -1;
        for (auto& edge : edges) {
            int u = get<0>(edge);
            int v = get<1>(edge);
            long long w = get<2>(edge);
            
            if (dist[u] + w < dist[v]) {
                dist[v] = dist[u] + w;
                parent[v] = u;
                x = v; // This node is part of or affected by negative cycle
            }
        }
    }
    
    if (x == -1) {
        cout << "NO" << endl;
    } else {
        // Trace back to find a node definitely in the cycle
        // Go back n steps to ensure we're in the cycle
        for (int i = 0; i < n; i++) {
            x = parent[x];
        }
        
        // Now trace the cycle
        vector<int> cycle;
        int start = x;
        
        while (true) {
            cycle.push_back(x);
            x = parent[x];
            if (x == start) {
                cycle.push_back(x);
                break;
            }
        }
        
        // Reverse to get correct order
        reverse(cycle.begin(), cycle.end());
        
        cout << "YES" << endl;
        for (int node : cycle) {
            cout << node << " ";
        }
        cout << endl;
    }
    
    return 0;
}

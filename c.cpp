#include <iostream>
#include<bits/stdc++.h>
using namespace std;
const long long INF = 1e18;

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
    
    vector<long long> dist(n + 1, INF);
    vector<int> parent(n + 1, -1);
    
    dist[1] = 0;
    
    int x = -1;
    
    for (int i = 0; i < n; i++) {
        x = -1;
        for (auto& edge : edges) {
            int u = get<0>(edge);
            int v = get<1>(edge);
            long long w = get<2>(edge);
            
            if (dist[u] + w < dist[v]) {
                dist[v] = dist[u] + w;
                parent[v] = u;
                x = v;
            }
        }
    }
    
    if (x == -1) {
        cout << "NO" << endl;
    } else {
        for (int i = 0; i < n; i++) {
            x = parent[x];
        }
        
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
        
        reverse(cycle.begin(), cycle.end());
        
        cout << "YES" << endl;
        for (int node : cycle) {
            cout << node << " ";
        }
        cout << endl;
    }
    
    return 0;
}

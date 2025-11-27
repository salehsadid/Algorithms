#include <bits/stdc++.h>
using namespace std;

int primsMST(int V, vector<pair<int, int>> adj[]) {
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
    vector<bool> visited(V, false);
    int cost = 0;
    pq.push({0, 0}); 
    
    while (!pq.empty()) {
        int w = pq.top().first;
        int u = pq.top().second;
        pq.pop();
        
        if (visited[u]) continue;
        
        visited[u] = true;
        cost += w;
        
        for (auto &edge : adj[u]) {
            int v = edge.first;
            int weight = edge.second;
            
            if (!visited[v]) {
                pq.push({weight, v});
            }
        }
    }
    
    return cost;
}

int main() {
     
    int V, E;
    cin >> V >> E;
    vector<pair<int, int>> adj[V];    
    for (int i = 0; i < E; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        adj[u].push_back({v, w});
        adj[v].push_back({u, w});
    }
    
    int mstCost = primsMST(V, adj);
    cout << "Cost: " << mstCost << endl;
    
    return 0;
}

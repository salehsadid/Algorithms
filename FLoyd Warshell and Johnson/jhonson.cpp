#include <bits/stdc++.h>
using namespace std;

#define INF 1e9

// Bellman-Ford Algorithm
bool bellmanFord(int V, vector<vector<int>>& edges, vector<int>& dist, int src) {
    dist.assign(V, INF);
    dist[src] = 0;
    
    // Relax edges V-1 times
    for (int i = 0; i < V - 1; i++) {
        for (auto& e : edges) {
            int u = e[0], v = e[1], w = e[2];
            if (dist[u] != INF && dist[u] + w < dist[v]) {
                dist[v] = dist[u] + w;
            }
        }
    }
    
    // Check for negative cycle
    for (auto& e : edges) {
        int u = e[0], v = e[1], w = e[2];
        if (dist[u] != INF && dist[u] + w < dist[v]) {
            return false;
        }
    }
    return true;
}

// Dijkstra's Algorithm
void dijkstra(int V, vector<pair<int, int>> adj[], vector<int>& dist, int src) {
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
    
    dist.assign(V, INF);
    dist[src] = 0;
    pq.push({0, src});
    
    while (!pq.empty()) {
        int d = pq.top().first;
        int u = pq.top().second;
        pq.pop();
        
        if (d > dist[u]) continue;
        
        for (auto& edge : adj[u]) {
            int v = edge.first;
            int w = edge.second;
            
            if (dist[u] + w < dist[v]) {
                dist[v] = dist[u] + w;
                pq.push({dist[v], v});
            }
        }
    }
}

// Johnson's Algorithm
void johnsonAlgorithm(int V, vector<vector<int>>& edges) {
    
    // Step 1: Add new vertex and edges with weight 0
    vector<vector<int>> modifiedEdges = edges;
    for (int i = 0; i < V; i++) {
        modifiedEdges.push_back({V, i, 0});
    }
    
    // Step 2: Run Bellman-Ford from new vertex
    vector<int> h;
    if (!bellmanFord(V + 1, modifiedEdges, h, V)) {
        cout << "Negative cycle detected!" << endl;
        return;
    }
    
    // Step 3: Reweight edges
    vector<pair<int, int>> adj[V];
    for (auto& e : edges) {
        int u = e[0], v = e[1], w = e[2];
        int newW = w + h[u] - h[v];
        adj[u].push_back({v, newW});
    }
    
    // Step 4: Run Dijkstra from each vertex
    cout << "All-pairs shortest paths:\n";
    for (int u = 0; u < V; u++) {
        vector<int> d;
        dijkstra(V, adj, d, u);
        
        // Print distances
        cout << "From vertex " << u << ": ";
        for (int v = 0; v < V; v++) {
            if (d[v] == INF) {
                cout << "INF ";
            } else {
                // Restore original weight
                cout << (d[v] - h[u] + h[v]) << " ";
            }
        }
        cout << endl;
    }
}

int main() {
    
    int V = 4;
    
    // Edges: {source, destination, weight}
    vector<vector<int>> edges = {
        {0, 1, -5},
        {0, 2, 2},
        {0, 3, 3},
        {1, 2, 4},
        {2, 3, 1}
    };
    
    johnsonAlgorithm(V, edges);
    
    return 0;
}

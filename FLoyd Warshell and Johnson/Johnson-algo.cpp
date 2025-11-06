#include <bits/stdc++.h>
using namespace std;

#define INF 1e9

// Bellman-Ford algorithm to find shortest paths from source
bool bellmanFord(int V, vector<vector<int>>& edges, vector<int>& dist, int src) {
    dist.assign(V, INF);
    dist[src] = 0;
    
    // Relax all edges V-1 times
    for (int i = 0; i < V - 1; i++) {
        for (auto& edge : edges) {
            int u = edge[0], v = edge[1], w = edge[2];
            if (dist[u] != INF && dist[u] + w < dist[v]) {
                dist[v] = dist[u] + w;
            }
        }
    }
    
    // Check for negative weight cycles
    for (auto& edge : edges) {
        int u = edge[0], v = edge[1], w = edge[2];
        if (dist[u] != INF && dist[u] + w < dist[v]) {
            return false; // Negative cycle detected
        }
    }
    return true;
}

// Dijkstra's algorithm to find shortest paths from source
void dijkstra(int V, vector<pair<int, int>> adj[], vector<int>& dist, int src) {
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
    
    dist.assign(V, INF);
    dist[src] = 0;
    pq.push({0, src});
    
    while (!pq.empty()) {
        int u = pq.top().second;
        int d = pq.top().first;
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
    
    // Step 1: Add a new vertex (V) and connect it to all vertices with weight 0
    vector<vector<int>> modifiedEdges = edges;
    for (int i = 0; i < V; i++) {
        modifiedEdges.push_back({V, i, 0});
    }
    
    // Step 2: Run Bellman-Ford from the new vertex
    vector<int> h;
    if (!bellmanFord(V + 1, modifiedEdges, h, V)) {
        cout << "Graph contains negative weight cycle" << endl;
        return;
    }
    
    // Step 3: Reweight the edges
    vector<pair<int, int>> adj[V];
    for (auto& edge : edges) {
        int u = edge[0], v = edge[1], w = edge[2];
        int newWeight = w + h[u] - h[v];
        adj[u].push_back({v, newWeight});
    }
    
    // Step 4: Run Dijkstra from each vertex
    vector<vector<int>> dist(V, vector<int>(V));
    
    for (int u = 0; u < V; u++) {
        vector<int> d;
        dijkstra(V, adj, d, u);
        
        // Restore original weights
        for (int v = 0; v < V; v++) {
            if (d[v] == INF) {
                dist[u][v] = INF;
            } else {
                dist[u][v] = d[v] - h[u] + h[v];
            }
        }
    }
    
    // Print the result
    cout << "All-pairs shortest paths:\n";
    for (int i = 0; i < V; i++) {
        for (int j = 0; j < V; j++) {
            if (dist[i][j] == INF) {
                cout << "INF ";
            } else {
                cout << dist[i][j] << " ";
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

#include <bits/stdc++.h>
using namespace std;

// Function to find MST using Prim's Algorithm
int primsMST(int V, vector<pair<int, int>> adj[]) {
    
    // Priority queue to store {weight, vertex}
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
    
    vector<bool> visited(V, false);
    int cost = 0;
    
    // Start from vertex 0
    pq.push({0, 0}); // {weight, vertex}
    
    while (!pq.empty()) {
        int w = pq.top().first;
        int u = pq.top().second;
        pq.pop();
        
        // Skip if already visited
        if (visited[u]) continue;
        
        // Mark as visited and add weight to MST
        visited[u] = true;
        cost += w;
        
        // Add all adjacent vertices to priority queue
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
    cout << "Enter the number of vertices: ";
    cin >> V;
    cout << "Enter the number of edges: ";
    cin >> E;
    
    // Adjacency list to store graph
    vector<pair<int, int>> adj[V];
    
    cout << "Enter edges in format (source destination weight):\n";
    
    for (int i = 0; i < E; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        
        // Since it's an undirected graph, add edge in both directions
        adj[u].push_back({v, w});
        adj[v].push_back({u, w});
    }
    
    int mstCost = primsMST(V, adj);
    cout << "Minimum Spanning Tree cost: " << mstCost << endl;
    
    return 0;
}

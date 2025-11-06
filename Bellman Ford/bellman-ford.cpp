#include <bits/stdc++.h>
using namespace std;
#define INF 1e9

void bellmanFord(int V, int E, vector<vector<int>>& edges, int src) {
    
    vector<int> dist(V, INF);
    dist[src] = 0;
    
    for (int i = 0; i < V - 1; i++) {
        for (int j = 0; j < E; j++) {
            int u = edges[j][0];
            int v = edges[j][1];
            int w = edges[j][2];
            
            if (dist[u] != INF && dist[u] + w < dist[v]) {
                dist[v] = dist[u] + w;
            }
        }
    }
    
    bool hasNegativeCycle = false;
    for (int j = 0; j < E; j++) {
        int u = edges[j][0];
        int v = edges[j][1];
        int w = edges[j][2];
        
        if (dist[u] != INF && dist[u] + w < dist[v]) {
            hasNegativeCycle = true;
            break;
        }
    }
    
    if (hasNegativeCycle) {
        cout << "Graph contains negative weight cycle!" << endl;
    } else {
        cout << "\nShortest distances from source " << src << ":\n";
        for (int i = 0; i < V; i++) {
            cout << "Vertex " << i << ": ";
            if (dist[i] == INF) {
                cout << "INF" << endl;
            } else {
                cout << dist[i] << endl;
            }
        }
    }
}

int main() {
    
    int V, E;
    cin >> V >> E;
    vector<vector<int>> edges;
    
    for (int i = 0; i < E; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        edges.push_back({u, v, w});
    }
    int src;
    cin >> src;
    bellmanFord(V, E, edges, src);
    
    return 0;
}

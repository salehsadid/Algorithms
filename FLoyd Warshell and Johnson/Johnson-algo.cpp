#include <iostream>
#include <vector>
#include <queue>
using namespace std;

const int INF = 1000000000;

bool bellmanFord(int n, vector<vector<int>>& edges, vector<int>& h, int src) {
    h.assign(n, INF);
    h[src] = 0;
    
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < edges.size(); j++) {
            int u = edges[j][0];
            int v = edges[j][1];
            int w = edges[j][2];
            
            if (h[u] != INF && h[u] + w < h[v]) {
                h[v] = h[u] + w;
            }
        }
    }
    
    for (int j = 0; j < edges.size(); j++) {
        int u = edges[j][0];
        int v = edges[j][1];
        int w = edges[j][2];
        
        if (h[u] != INF && h[u] + w < h[v]) {
            return false; 
        }
    }
    return true; 
}

void dijkstra(int n, vector<pair<int, int>> adj[], vector<int>& dist, int src) {
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
    
    dist.assign(n, INF);
    dist[src] = 0;
    pq.push({0, src});
    
    while (!pq.empty()) {
        int d = pq.top().first;
        int u = pq.top().second;
        pq.pop();
        
        if (d > dist[u]) continue;
        
        for (int i = 0; i < adj[u].size(); i++) {
            int v = adj[u][i].first;
            int w = adj[u][i].second;
            
            if (dist[u] + w < dist[v]) {
                dist[v] = dist[u] + w;
                pq.push({dist[v], v});
            }
        }
    }
}

void johnsonAlgo(int n, vector<vector<int>>& edges) {
    
   
    vector<vector<int>> newEdges = edges;
    for (int i = 0; i < n; i++) {
        newEdges.push_back({n, i, 0});
    }
    
    vector<int> h; 
    if (!bellmanFord(n + 1, newEdges, h, n)) {
        cout << "Graph contains negative weight cycle!\n";
        return;
    }
    
    vector<pair<int, int>> adj[n];
    for (int i = 0; i < edges.size(); i++) {
        int u = edges[i][0];
        int v = edges[i][1];
        int w = edges[i][2];
        
        int newW = w + h[u] - h[v];
        adj[u].push_back({v, newW});
    }
    
    vector<vector<int>> dist(n, vector<int>(n));
    
    for (int src = 0; src < n; src++) {
        vector<int> d;
        dijkstra(n, adj, d, src);
        
        for (int dst = 0; dst < n; dst++) {
            if (d[dst] == INF) {
                dist[src][dst] = INF;
            } else {
                dist[src][dst] = d[dst] - h[src] + h[dst];
            }
        }
    }
    
    for (int i = 0; i < n; i++) {
        cout << "From vertex " << i << ": ";
        for (int j = 0; j < n; j++) {
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
    
    int n = 4;

    vector<vector<int>> edges = {
        {0, 1, -5},  
        {0, 2, 2},   
        {0, 3, 3},   
        {1, 2, 4},   
        {2, 3, 1}    
    };
    
    johnsonAlgo(n, edges);
    
    return 0;
}

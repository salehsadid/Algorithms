#include <iostream>
#include <vector>
#include <queue>
#include <climits>
#include <cstring>
using namespace std;

class MaxFlow {
private:
    vector<vector<int>> capacity;
    vector<vector<int>> adj;
    int n;
    
    bool bfs(int source, int sink, vector<int>& parent) {
        vector<bool> visited(n, false);
        queue<int> q;
        q.push(source);
        visited[source] = true;
        parent[source] = -1;
        
        while (!q.empty()) {
            int u = q.front();
            q.pop();
            
            for (int v : adj[u]) {
                if (!visited[v] && capacity[u][v] > 0) {
                    q.push(v);
                    parent[v] = u;
                    visited[v] = true;
                    if (v == sink) return true;
                }
            }
        }
        return false;
    }
    
public:
    MaxFlow(int nodes) : n(nodes) {
        capacity.resize(n, vector<int>(n, 0));
        adj.resize(n);
    }
    
    void addEdge(int u, int v, int cap) {
        capacity[u][v] = cap;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    
    int fordFulkerson(int source, int sink) {
        vector<int> parent(n);
        int maxFlow = 0;
        
        while (bfs(source, sink, parent)) {
            int pathFlow = INT_MAX;
            
            for (int v = sink; v != source; v = parent[v]) {
                int u = parent[v];
                pathFlow = min(pathFlow, capacity[u][v]);
            }
            
            for (int v = sink; v != source; v = parent[v]) {
                int u = parent[v];
                capacity[u][v] -= pathFlow;
                capacity[v][u] += pathFlow;
            }
            
            maxFlow += pathFlow;
        }
        
        return maxFlow;
    }
};

int main() {
    int nodes = 6;
    MaxFlow graph(nodes);
    
    graph.addEdge(0, 1, 16);
    graph.addEdge(0, 2, 13);
    graph.addEdge(1, 2, 10);
    graph.addEdge(1, 3, 12);
    graph.addEdge(2, 1, 4);
    graph.addEdge(2, 4, 14);
    graph.addEdge(3, 2, 9);
    graph.addEdge(3, 5, 20);
    graph.addEdge(4, 3, 7);
    graph.addEdge(4, 5, 4);
    
    int source = 0, sink = 5;
    cout << "Maximum Flow: " << graph.fordFulkerson(source, sink) << endl;
    
    return 0;
}
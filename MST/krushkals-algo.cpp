// Simple Kruskal's algorithm that reads graph from stdin.
// Input format (simple):
// First line: V E
// Next E lines: u v w  (one edge per line)
// Vertices should be numbered 0..V-1 (if you use 1..V the program will auto-detect and convert).

#include <bits/stdc++.h>
using namespace std;

struct Edge { int u, v, w; };

int findp(vector<int>& parent, int x) {
    // simple iterative find with path compression
    while (parent[x] != x) {
        parent[x] = parent[parent[x]];
        x = parent[x];
    }
    return x;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int V, E;
    // Read number of vertices and edges
    if (!(cin >> V >> E)) {
        cerr << "Failed to read V and E. Expected: V E\n";
        return 1;
    }

    // Build adjacency list and edge list.
    vector<Edge> edges;
    edges.reserve(E);
    vector<vector<pair<int,int>>> adj(V); // adjacency list: adj[u] = vector of {v, w}

    bool read_ok = true;
    int maxVertex = -1;
    for (int i = 0; i < E; ++i) {
        int u, v, w;
        if (!(cin >> u >> v >> w)) {
            cerr << "Failed to read edge #" << i+1 << ". Expected: u v w\n";
            return 1;
        }
        edges.push_back({u, v, w});
        maxVertex = max(maxVertex, max(u, v));
    }

    // Detect if input is 1-based (e.g., vertices numbered 1..V) and convert to 0-based.
    bool one_based = (maxVertex >= V);

    // Fill adjacency list and normalize indices if needed.
    for (auto &e : edges) {
        int u = e.u;
        int v = e.v;
        int w = e.w;
        if (one_based) { u -= 1; v -= 1; }
        // ignore invalid entries after conversion
        if (u < 0 || u >= V || v < 0 || v >= V) continue;
        adj[u].push_back({v, w});
        adj[v].push_back({u, w});
        // store normalized values back for Kruskal
        e.u = u; e.v = v;
    }

    // sort edges by weight (ascending) for Kruskal
    sort(edges.begin(), edges.end(), [](const Edge &a, const Edge &b){
        return a.w < b.w;
    });

    // simple union-find arrays
    vector<int> parent(V), rankv(V, 0);
    for (int i = 0; i < V; ++i) parent[i] = i;

    long long mst_wt = 0;
    int edges_used = 0;

    // Optional: you can print adjacency list for debugging or confirmation
    // Uncomment the following block if you want to see adj lists on output.
    /*
    cout << "Adjacency list:\n";
    for (int i = 0; i < V; ++i) {
        cout << i << ": ";
        for (auto &p : adj[i]) cout << "(" << p.first << "," << p.second << ") ";
        cout << '\n';
    }
    cout << '\n';
    */

    cout << "Edges of MST are\n";
    for (const auto &e : edges) {
        if (edges_used == V - 1) break;
        if (e.u < 0 || e.u >= V || e.v < 0 || e.v >= V) continue; // skip invalid
        int pu = findp(parent, e.u);
        int pv = findp(parent, e.v);
        if (pu != pv) {
            // take this edge
            cout << e.u << " - " << e.v << '\n';
            mst_wt += e.w;
            edges_used++;
            // union by rank
            if (rankv[pu] < rankv[pv]) parent[pu] = pv;
            else if (rankv[pu] > rankv[pv]) parent[pv] = pu;
            else { parent[pv] = pu; rankv[pu]++; }
        }
    }

    cout << "\nWeight of MST is " << mst_wt << '\n';
    return 0;
}
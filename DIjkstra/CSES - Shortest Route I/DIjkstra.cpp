#include <bits/stdc++.h>
using namespace std ;
#define ll long long
const ll INF = 1e18;

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    ll n, m;
    cin>>n>>m; // na mene nodes , m mane vertex

    vector<pair<ll,ll>> g[n+1]; // eita adjacency list rakhar jonne


    for(ll i=0; i<m; i++)
    {
        ll x, y, z;
        cin>>x>>y>>z;

        g[x].push_back({y, z}); // directed bole shudu eita nisi
       // g[y].push_back({x, z}); // undirected hole eitao nitam

    }
    // ei porjonto input nilam graph ta then adj list e rakhlam -----------------

    //distANCE list banabo ------------
    vector<ll> d(n+1, INF); // n number of vertex er jonne nisi ... n+1 cz 1 theke start hoise

    //-------------------
    //priority queue banabo min heap er jonne , ami min number ta niye kaaj krtesi

    priority_queue<pair<ll,ll> , vector<pair<ll,ll>> , greater<pair <ll,ll>>> pq; // ekhane first ll hocche distance , sec ll hocche node
    // ashole ekhane ami pq er moddhe ekta node er shathe connected node gula pabo , oitar moddhe jetar lowest value oita niye kaaj korbo


    d[1]=0; // src theke src ke 0 dhore rakhlam
    pq.push(make_pair (0LL,1LL)); // first node theke first node er distance 0

    //---------
    // ekhon main while loop jeta diye amra traverse kortesi
    while(!pq.empty()){

        pair<ll ,ll> top= pq.top();
        pq.pop();

        // ekhane ami ashole current node niye kaaj kortesi
        ll curr_node= top.second; // second er moddhe node
        ll curr_distance=top.first; // first er moddhe distance rakhsilam

        if(curr_distance > d[curr_node]) continue; // current node er distance jodi amar current distance theke choto hoi taile baad


        for ( size_t i=0; i< g[curr_node].size();i++){ // no of edges with current node .. shoman loop cholbe

            ll child_node = g[curr_node][i].first; // adj list er moddhe first ta chilo node jaar shathe enge ,, mane to ** node
            ll child_distance = g[curr_node][i].second; // edge cost

            if(curr_distance + child_distance < d[child_node]){// ekhane current node er distance er shathe , er connected edge mane child er distance
                                                                //er jog kore jodi dekhi oita distance array te child er je distance save kora chilo taar theke kom taile update korbo
                d[child_node]=curr_distance + child_distance;
                pq.push(make_pair (d[child_node], child_node)); // updated distance pq te push kore rekhe dilam
            }
        }
    }
    for (ll i=1; i<=n;i++){
        cout<<d[i]<<" ";
    }


    return 0;
}

// TLE khaisi



#include <bits/stdc++.h>
using namespace std ;
#define ll long long
const ll INF = 1e18;

void dijkstra(ll n,vector<pair<ll,ll>> g[],ll a, ll b, ll res[],ll i)
{

    vector<ll> d(n+1, INF);


    priority_queue<pair<ll,ll>, vector<pair<ll,ll>>, greater<pair <ll,ll>>> pq;

    d[a]=0;
    pq.push(make_pair (0,a));


    while(!pq.empty())
    {

        pair<ll,ll> top= pq.top();
        pq.pop();


        ll curr_node= top.second;
        ll curr_distance=top.first;

        if(curr_distance > d[curr_node]) continue;

        for ( size_t i=0; i< g[curr_node].size(); i++)
        {

            ll child_node = g[curr_node][i].first;
            ll child_distance = g[curr_node][i].second;

            if(curr_distance + child_distance < d[child_node])
            {

                d[child_node]=curr_distance + child_distance;
                pq.push(make_pair (d[child_node], child_node));
            }
        }
    }
    if(d[b]<INF)
    {
        res[i]=d[b];

    }
    else res[i]=-1;

}


int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);


    ll n, m,q;

    cin>>n>>m>>q;
    ll res[q];
    vector<pair<ll,ll>> g[n+1];


    for(ll i=0; i<m; i++)
    {
        ll x, y, z;
        cin>>x>>y>>z;

        g[x].push_back({y, z}); // directed bole shudu eita nisi
        g[y].push_back({x, z}); // undirected hole eitao nitam

    }

    for(ll i=0; i<q; i++)
    {
        ll a,b;
        cin>>a>>b;
        dijkstra(n,g,a,b,res,i);

    }
    for(ll i=0; i< q; i++)
    {
        cout<<res[i]<<endl;

    }



    return 0;
}

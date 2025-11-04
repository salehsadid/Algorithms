#include<bits/stdc++.h>
using namespace std;
#define INF 100000000

void floyd(vector<vector<int>> &dist)
{
    int v= dist.size();
    for(int k=0; k<v; k++)
    {
        for(int i=0; i<v; i++)
        {
            for(int j=0; j<v; j++)
            {   //333if(dist[i][k]!=INF && dist[k][j]!=INF )
                dist[i][j]=min(dist[i][j],dist[i][k]+dist[k][j]);
            }
        }
    }

}
int main()
{
    vector<vector<int>> dist=
    {
        {0, 4, INF, 5, INF},
        {INF, 0, 1, INF, 6},
        {2, INF, 0, 3, INF},
        {INF, INF, 1, 0, 2},
        {1, INF, INF, 4, 0}
    };

    floyd(dist);
    for(int i = 0; i<dist.size(); i++) {
        for(int j = 0; j<dist.size(); j++) {
            cout<<dist[i][j]<<" ";
        }
        cout<<endl;


}
}

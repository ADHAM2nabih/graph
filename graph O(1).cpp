#include <map>
#include <vector>
#include <iostream>
#include <set>
#include <queue>
#include <algorithm>
#include <utility>
#define ll long long

using namespace std;

int n,m,first_node ;

void print(vector<int>graph[],int v)
{
    for (int i = 1; i <= v ; i++)
    {
        int f = graph[i].size();
        cout<<i<< " : ";
        for (int j = 0; j < f; j++)
        {
            cout << graph[i][j] << " ";
        }
        cout << endl;
    }
}
void print(vector<long>g,int v)
{
    for (int i = 1; i <=v ; i++)
    {
        cout<<g[i]<<" ";
    }
    cout<<endl;
}
void print(vector<vector<ll>>graph,int v)
{
    for (int i = 1; i <= v ; i++)
    {
        cout<<i<< " : ";
        for (int j = 1; j <= v; j++)
        {
            cout << graph[i][j] << "    ";
        }
        cout << endl;
    }
}

int degree(vector<int>graph[],int node)
{
    return graph[node].size();
}

void dfs(int node,vector<int>graph[],vector<int>&visited)
{
    cout<<node<<" ";
    visited[node] = 1;
    int siz = graph[node].size();
    for (int j = 0; j <siz ; j++)
    {
        if(!visited[graph[node][j]])
        {
            dfs(graph[node][j],graph,visited);

        }
    }
}

void bfs(int node, vector<int>graph[], vector<int>& visited, queue<int>& que)
{

    visited[node] = 1;
    que.push(node);
    while (!que.empty())
    {
        int f = que.front();
        int siz = graph[f].size();
        que.pop();
        cout << f << " ";
        for (int i = 0; i < siz; i++)
        {
            if (!visited[graph[f][i]])
            {
                que.push(graph[f][i]);
                visited[graph[f][i]] = 1;
            }
        }
    }
}

int count_graphs(vector<int>graph[],int v, vector<int>& visited)
{
    int cnt = 0;
    for (int i = 1; i <= v; i++)
    {
        if (!visited[i])
        {
            dfs(i, graph, visited);
            cout<<" ";
            cnt++;
        }
    }
    //cout<<"NUMBER OF CONNECTED GRAPHS : ";
    return cnt;
}

int shortest_path(int start,int target,vector<int>graph[])
{
    if (start == target)
    {
        return 0;
    }

    vector<int>visited(n+1,0);
    queue<pair<int, int>> q;
    q.push({start, 0});
    visited[start]=1;

    while (!q.empty())
    {
        int node = q.front().first ,
            dist = q.front().second ,
            n = graph[node].size();

        q.pop();

        for (int i=0; i<n; i++)
        {
            if (graph[node][i] == target)
            {
                return dist + 1;
            }

            if (!visited[graph[node][i]])
            {
                visited[graph[node][i]]=1;
                q.push({graph[node][i], dist + 1});
            }
        }
    }
    return -1;
}

/////////////////////////////////////////directed

bool isCyclic_util_directed(vector<int> adj[], vector<bool> visited, int curr)
{
    if(visited[curr]==true)
        return true;

    visited[curr] = true;
    bool f = false;

    int x =adj[curr].size();
    for(int i=0; i<x; ++i)
    {
        f = isCyclic_util_directed(adj, visited, adj[curr][i]);
        if(f==true)
            return true;
    }

    return false;
}

bool isCyclic_directed(int V, vector<int> adj[])
{
    vector<bool> visited(V+1,false);
    bool f = false;

    for(int i=1; i<=V; ++i)
    {
        visited[i] = true;
        int x = adj[i].size();
        for(int j=0; j<x; ++j)
        {

            if(isCyclic_util_directed(adj,visited,adj[i][j]))
                return true;
        }
        visited[i] = false;
    }

    return false;
}
///////////////////////////////////////////////////directed


////////////////////////////////////////////////undirected

bool isCyclic_util_undirected(vector<int> adj[], vector<int> visited, int curr)
{
    if(visited[curr]==2)
        return true;

    visited[curr] = 1;
    bool f = false;
    int x = adj[curr].size();
    for(int i=0; i<x; ++i)
    {
        if(visited[adj[curr][i]]==1)
            visited[adj[curr][i]] = 2;
        else
        {

            if(isCyclic_util_undirected(adj, visited, adj[curr][i]))
                return true;
        }
    }
    return false;
}

bool isCyclic_undirected(int V,vector<int> adj[])
{
    vector<int> visited(V+1,0);
    bool f = false;
    for(int i=1; i<=V; ++i)
    {
        visited[i] = 1;
        int x =adj[i].size();
        for(int j=0; j<x; ++j)
        {
            f = isCyclic_util_undirected(adj,visited,adj[i][j]);
            if(f==true)
                return true;
        }
        visited[i] = 0;
    }
    return false;
}
///////////////////////////////////////////////////undirected

/////////////////////////////////////////////////// dijkistra


void dijkstra(int start, vector<pair<int, int>> adj[], int V)
{
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
    vector<int> dist(V+1, INT_MAX);
    dist[start] = 0;
    pq.push({0, start});

    while (!pq.empty())
    {
        int u = pq.top().second;
        pq.pop();

        int q = adj[u].size();
        for (int i=0; i<q; i++)
        {
            int v = adj[u][i].first;
            int weight = adj[u][i].second;

            if (dist[u] + weight < dist[v])
            {
                dist[v] = dist[u] + weight;
                pq.push({dist[v], v});
            }
        }
    }

    cout << "Node Distance from Source" << endl;
    for (int i = 1 ; i<=V ; i++)
    {
        cout << i << "   " << dist[i] << endl;
    }
}
////////////////////////////////////////////////bellman ford
int did = 1e6+5;
vector<long>dist(did),to(did),from(did),we(did);

bool bellmanford(int source)
{
    bool x=0;
    for(int i=1; i<n; i++) dist[i]=LONG_MAX;
    dist[source]=0;
    for(int i=0; i<n; i++)  ///////n-1 for bellman ford       n for detection of negative cycles
    {
        int flag=0;
        for(int j=0; j<m; j++)
        {
            ll u = from[j], v = to[j], w = we[j];
            if(dist[u]+w<dist[v])
            {
                dist[v] = dist[u]+w;
                flag = 1;
            }
        }
        if(i==n-1 && flag) x=1;
    }
    return x;  // for detecting negative cycles
}

///////////////////////////////////////////////////

pair<vector<vector<ll>>,bool> Floyd_Warshall(vector<vector<ll>>v,int n)
{
    bool flag =0;
    for(int k=1; k<=n; k++)
    {
        for(int i=1; i<=n; i++)
        {
            for(int j=1; j<=n; j++)
            {
                v[i][j] = min(v[i][j],v[i][k]+v[k][j]);
            }
        }
    }
    for(int i=1; i<=n; i++)
    {
        if(v[i][i]<0)
        {
            flag=1;
            break;
        }
    }
    return {v,flag};
}

////////////////////////////////////////////////////

const int N=2e5+5;
int par[N],sz[N];

void init(int n)
{
    for(int i=1; i<=n; i++)
    {
        par[i]=i;
        sz[i]=1;
    }
}

int findparent(int u)
{
    if(par[u]==u)
        return u;
    return par[u]=findparent(par[u]);
}

void connect(int u,int v)
{
    u= findparent(u);
    v= findparent(v);
    if(u==v)return;

    if(sz[v]>sz[u])
    {
        par[u]=v;
        sz[v]+=sz[u];
    }
    else
    {
        par[v]=u;
        sz[u]+=sz[v];
    }
}

ll kruskal(pair<ll,pair<ll,ll>>p[])
{

    ll x,y,cost=0,mincost=0;
    for(int i=0; i<m; i++)
    {
        x = p[i].second.first;
        y = p[i].second.second;
        cost = p[i].first;
        if(findparent(x)!=findparent(y))
        {
            mincost +=cost;
            connect(x,y);
        }
    }
    return mincost;
}

///////////////////////////////////////////////////

int main()
{
    cin>>n>>m;

    vector<vector<ll>> x(n+1, vector<ll>(n+1,INT_MAX));
    queue<int>que;

    int t;
    cout<<"1- weighted  2-unweighted : ";
    cin>>t;
    if(t==1)
    {
        init(n);
        vector<pair<int, int>> graph[n+1];
        pair<ll,pair<ll,ll>> p[m];

        for (int i = 0; i < m; i++)
        {
            int u, v, weight;
            cin >> u >> v >> weight;
            graph[u].push_back({v, weight});
            x[u][v]=weight;
            x[v][u]=weight; // detecting negative cycles in floyd warshall
            graph[v].push_back({u, weight});
            p[i] = {weight,{u,v}};

            from[i] = u; //bellman ford
            to[i] = v;
            we[i] = weight;
        }

        first_node = -1;
        for (int i = 1; i <= n; i++)
        {
            if (!graph[i].empty())
            {
                first_node = i;
                break;
            }
        }

        cout<<"1-negative  2-positive ( graph ) "<<endl;
        int negative ;
        cin>>negative;
        if(negative==1)
        {
            cout<<"there is a negative cycle using bellmanford : "<<bellmanford(first_node)<<endl;
            //print(dist,m);   //if you want to print make a lil change in the original function

            pair<vector<vector<ll>>,bool>f = Floyd_Warshall(x,n);
            cout << "Negative cycle detected by floyd warshall : "<<f.second <<endl;
            //print(f.first,n); //if you want to print make a lil change in the original function

            return 0;
        }

        dijkstra(first_node, graph, n);

        pair<vector<vector<ll>>,bool>f = Floyd_Warshall(x,n);
        print(f.first,n);

        sort(p,p+m);
        cout<<"minimum spanning tree is : "<<kruskal(p)<<endl;
        /*

        1 2 4
        1 3 8
        2 3 11
        3 4 7
        3 6 1
        2 5 8
        4 5 2
        4 6 6
        6 7 2
        5 7 4
        9 8 9
        7 8 10
        9 7 14
        5 9 7

        */
    }

    else
    {
        vector<int>graph[n+1];
        for(int i=0; i<m; i++)
        {
            int r,c;
            cin>>r>>c;
            graph[r].push_back(c) ;
            graph[c].push_back(r) ;
        }

        cout<<isCyclic_undirected(n,graph)<<endl;


        first_node = -1;
        for (int i = 1; i <= n; i++)
        {
            if (!graph[i].empty())
            {
                first_node = i;
                break;
            }
        }

        if(first_node!=-1)
        {
            vector<int>visited(n+1,0);
            dfs(first_node,graph,visited);
            cout<<endl;

            vector<int>visited2(n+1,0);
            bfs(first_node,graph,visited2,que);
            cout<<endl;

            vector<int>visited3(n+1,0);
            cout<<count_graphs(graph,n,visited3)<<endl;

            cout<<"shortest path from first node to n : "<<shortest_path(first_node,n,graph)<<endl;

            print(graph,n);
        }

    }






}



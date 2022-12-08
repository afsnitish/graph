//{ Driver Code Starts
#include<bits/stdc++.h>
using namespace std;

// } Driver Code Ends


class DisjointSet{
    vector<int> par, rank, size;
    public:
        // initialise the par and rank vector
        DisjointSet(int n){
            par.resize(n + 1);
            rank.resize(n + 1, 0);
            size.resize(n + 1, 1);
            for(int i = 0; i <= n; i++)par[i] = i;
        }
        // get the ultimate parent of a node 
        int findUpar(int node){
            if(par[node] == node)return node;
            return par[node] = findUpar(par[node]);
        }
        
        // union by rank
        void unionByRank(int u, int v){
            int ulp_u = findUpar(u);
            int ulp_v = findUpar(v);
            if(ulp_v == ulp_u)return;
            if(rank[ulp_u] < rank[ulp_v]){
                par[ulp_u] = ulp_v;
            }else if(rank[ulp_v] < rank[ulp_u]){
                par[ulp_v] = ulp_u;
            }else{
                par[ulp_v] = ulp_u;
                rank[ulp_u]++;
            }
        }
        
        // union by size (path compression)
        void unionBySize(int u, int v){
            int ulp_u = findUpar(u);
            int ulp_v = findUpar(v);
            if(ulp_u == ulp_v)return;
            if(size[ulp_u] > size[ulp_v]){
                par[ulp_v] = ulp_u;
                size[ulp_u] += size[ulp_v];
            }else{
                par[ulp_u] = ulp_v;
                size[ulp_v] += size[ulp_u];
            }
        }
};

class Solution
{
	public:
	//Function to find sum of weights of edges of the Minimum Spanning Tree.
    int spanningTree(int V, vector<vector<int>> adj[])
    {
        vector<pair<int, pair<int, int> > > edges(V);
        int edgeCount = (int)adj ->size();
        for(int i = 0; i < V; i++){
            for(auto edge : adj[i]){
                int v = edge[0];
                int w = edge[1];
                edges.push_back({w, {i, v}});
            }
        }
        sort(edges.begin(), edges.end());
        DisjointSet ds(V);
        int incl = 0, idx = 0, ans = 0;
        for(auto& edge : edges){
            int u = edge.second.first;
            int v = edge.second.second;
            int w = edge.first;
            if(ds.findUpar(u) != ds.findUpar(v)){
                ans += w;
                ds.unionBySize(u, v);
            }
        }
        return ans;
    }
};

//{ Driver Code Starts.


int main()
{
    int t;
    cin >> t;
    while (t--) {
        int V, E;
        cin >> V >> E;
        vector<vector<int>> adj[V];
        int i=0;
        while (i++<E) {
            int u, v, w;
            cin >> u >> v >> w;
            vector<int> t1,t2;
            t1.push_back(v);
            t1.push_back(w);
            adj[u].push_back(t1);
            t2.push_back(u);
            t2.push_back(w);
            adj[v].push_back(t2);
        }
        
        Solution obj;
    	cout << obj.spanningTree(V, adj) << "\n";
    }

    return 0;
}


// } Driver Code Ends

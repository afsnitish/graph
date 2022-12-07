#include <bits/stdc++.h>
#define ll long long int
using namespace std;

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


int main() {
    DisjointSet ds(7);
    ds.unionBySize(1, 2);
    ds.unionBySize(2, 3);
    ds.unionBySize(4, 5);
    ds.unionBySize(6, 7);
    ds.unionBySize(5, 6);
    
    // check if 3 and 7 lies in the same component or not
    if(ds.findUpar(3) == ds.findUpar(7)){
        cout<<"same\n";
    }else{
        cout<<"not same \n";
    }
    
    // adding the nodes 
    ds.unionBySize(3, 7);
    
    // check if 3 and 7 lies in the same component or not
    if(ds.findUpar(3) == ds.findUpar(7)){
        cout<<"same\n";
    }else{
        cout<<"not same\n";
    }
    
    return 0;
}

#include<bits/stdc++.h>
using namespace std;
#define int long long
int M=998244353;
// int BS(vector<vector<int>>&v,int mid){
//     int low=0,high=v.size(),mid1;
//     while(low<high){
//         mid1=(high+low)/2;
//         if(v[mid1][0] < mid)low=mid1+1;
//         else high=mid1;
//     }
//     return high;
// }
// int por(int a,int b,int M){
//     int w=1;
//     while(b){
//         if(b%2)w = (w*a)%M;
//         a=(a*a)%M;
//         b/=2;
//     }
//     return w;
// }
// int dp[200001];
// int Ans(int idx,int n,vector<vector<int>>&v){
//     if(idx>=n+1)return 1LL;
//     if(dp[idx] != -1)return dp[idx];
//     int ans=0;
//     // int st = BS(v,idx);
//     // while(st<v.size() && v[st][0]==idx){
//     //     ans += ((Ans(v[st][1]+1,n,v)*v[st][2]%M)*por(v[st][3]-v[st][2],M-2,M)%M);
//     //     ans %= M;
//     //     st+=1;
//     // }
//     for(int st=0;st<v.size();st+=1){
//         if(idx==v[st][0])ans += ((Ans(v[st][1]+1,n,v)*v[st][2]%M)*por(v[st][3]-v[st][2],M-2,M)%M);
//         ans %= M;
//     }
//     return dp[idx]=ans;
// }
int dfs(vector<int>G[],int m){
    priority_queue<vector<int>,vector<vector<int>>,greater<vector<int>>>pq;
    pq.push({0,1});
    int dp[m+1][m];
    for(int i=0;i<=m;i+=1){
        for(int j=0;j<m;j+=1){
            if(i!=1)dp[i][j]=1e9;
            else dp[i][j]=0;
        }
    }

    while(!pq.empty()){
        vector<int>v=pq.top();
        pq.pop();
        if(dp[v[1]][v[0]%G[v[1]].size()] <= v[0])continue;
        dp[v[1]][v[0]%G[v[1]].size()]=v[0];

        for(int i=0;i<G[v[1]].size();i+=1){
            int x = v[0]%G[v[1]].size();
            int cst = G[v[1]].size()-x+1;
            pq.push({v[0]+cst,v[1]});
        }
    }
    int ans=1e9;
    for(int i=0;i<m;i+=1){
        ans = min(ans,1LL*dp[m][i]);
    }
    return ans;
}
void solve(){
    int n,m,a,b;
    cin>>n>>m;
    vector<int>G[m+1];
    for(int i=0;i<n;i+=1){
        cin>>a>>b;
        G[a].push_back(b);
        G[b].push_back(a);
    }
    int t = dfs(G,m);
    
}
int32_t main(){
    int t=1;
    // cin>>t;
    while(t--){
        solve();
    }
    return 0;
}
// 3 3
// 1 2 1 3
// 3 3 1 2
// 1 3 2 3

// 8 5
// 1 3 1 2
// 1 5 1 6
// 1 4 4 5
// 5 5 1 7
// 4 5 1 2
// 4 5 2 5
// 3 3 2 7
// 1 2 1 3
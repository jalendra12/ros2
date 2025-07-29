#include<bits/stdc++.h>
using namespace std;
#define int long long
int M=998244353;
int BS(vector<vector<int>>&v,int mid){
    int low=0,high=v.size(),mid1;
    while(low<high){
        mid1=(high+low)/2;
        if(v[mid1][0] < mid)low=mid1+1;
        else high=mid1;
    }
    return high;
}
int por(int a,int b,int M){
    int w=1;
    while(b){
        if(b%2)w = (w*a)%M;
        a=(a*a)%M;
        b/=2;
    }
    return w;
}
int dp[200001];
int Ans(int idx,int n,vector<vector<int>>&v){
    if(idx>=n+1)return 1LL;
    if(dp[idx] != -1)return dp[idx];
    int ans=0;
    int st = BS(v,idx);
    while(st<v.size() && v[st][0]==idx){
        ans += ((Ans(v[st][1]+1,n,v)*v[st][2]%M)*por(v[st][3]-v[st][2],M-2,M)%M);
        ans %= M;
        st+=1;
    }
    // for(int st=0;st<v.size();st+=1){
    //     if(idx==v[st][0])ans += ((Ans(v[st][1]+1,n,v)*v[st][2]%M)*por(v[st][3]-v[st][2],M-2,M)%M);
    //     ans %= M;
    // }
    return dp[idx]=ans;
}
void solve(){
    int n,m,a,b,c,d;
    cin>>m>>n;
    memset(dp,-1,sizeof(dp));
    vector<vector<int>>v;
    for(int i=0;i<m;i+=1){
        cin>>a>>b>>c>>d;
        v.push_back({a,b,c,d});
    }
    sort(v.begin(),v.end());
    vector<int>prob(m,1);

    for(int i=0;i<m;i+=1){
        prob[i] = ((v[i][3]-v[i][2])*por(v[i][3],M-2,M))%M;
        if(i>0)prob[i]=(prob[i]*prob[i-1])%M;
    }
    cout<<((Ans(1,n,v)*prob[m-1])%M)<<endl;
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
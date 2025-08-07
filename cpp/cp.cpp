#include<bits/stdc++.h>
using namespace std;
int Par(int p,vector<int>&par){
    if(p==par[p])return p;
    else return par[p]=Par(par[p],par);
    // return (p==par[p])?p:(par[p]=Par(par[p],par));
}
void solve(){
    int n,a,b;
    cin>>n;
    vector<int>ans,par(2*n+2,-1),sz(2*n+2,1);
    for(int i=0;i<2*n+2;i+=1)par[i]=i;
    for(int i=0;i<n;i+=1){
        cin>>a>>b;
        a=Par(a,par);
        b=Par(b,par);
        if(a==b)continue;
        else if(sz[a]>sz[b]){
            sz[a]+=sz[b];
            par[b]=a;
        }else{
            sz[b]+=sz[a];
            par[a]=b;
        }
        ans.push_back(i+1);
    }
    cout<<ans.size()<<endl;
    for(auto x:ans)cout<<x<<" ";cout<<endl;

}
int main(){
    int t;
    cin>>t;
    while(t--)solve();
}

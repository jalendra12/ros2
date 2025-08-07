#include<bits/stdc++.h>
using namespace std;
void solve(){
    int n;cin>>n;
    vector<int>v(n);
    for(auto &x:v)cin>>x;
    vector<int>pos(n);
    for(int i=0;i<n;i+=1)pos[v[i]-1]=i;
    for(int i=0;i<n;i+=1){
        int isPos=0,maxi=n+2;
        for(int j=0;j<n;j+=1){
            if(j<pos[i] && v[pos[i]]<v[j])isPos+=1;
            else if(j>pos[i] && v[pos[i]]<v[j])isPos-=1;
            if(j>pos[i])maxi=min(maxi,v[j]);
        }
        if((isPos>0) || (2*n-v[pos[i]]<maxi))v[pos[i]]=2*n-v[pos[i]];
    }
    int ans=0;
    for(int i=0;i<n;i+=1){
        for(int j=i+1;j<n;j+=1){
            ans += (v[i]>v[j]);
        }
    }
    cout<<ans<<endl;
}
int main(){
    int t;
    cin>>t;
    while(t--)solve();
}

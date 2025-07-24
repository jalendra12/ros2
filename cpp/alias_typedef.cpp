#include<bits/stdc++.h>
using namespace std;
/// @brief typedefs don’t support templatization, but alias declarations do.
typedef
    unordered_map<int, int> // typedef
mp;

using vec = vector<int>;

template<typename T,typename S>
using map1 = map<T,S>; // alias

int main(){
    map1<int,int>mp1;
    mp1[2]+=1;
    mp1[1]+=1;

    mp1[21]+=1;
    mp1[11]+=1;

    for(auto x:mp1){
        cout<<x.first<<" "<<x.second<<endl;
    }
    return 0;
}
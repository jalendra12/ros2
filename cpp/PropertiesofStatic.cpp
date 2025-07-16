#include<bits/stdc++.h>
using namespace std;
class B{
 public:
 const static int a=20;//ISO C++ forbids in-class initialization of non-const static member
 static void f(){
    for(int i=1;i<=5;i+=1){
        cout<<i<<" ";
    }
    cout<<endl;
 }
};
int b=0;
int fun(){
    static int a=1;
    b += a;
    a+=1;
    return a;
}
int main(){
    // B::f();// Static Member function can be called without an object
    // cout<<(B::a)<<endl;
    for(int i=1;i<=5;i+=1)fun();
    cout<<b<<endl;
    /*
    What actually really happening:
    Directing the allocation of variables to the data/BSS segment for static storage duration, rather than the stack or heap.
    */
    return 0;
}
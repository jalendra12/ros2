#include<bits/stdc++.h>
using namespace std;
/*Macros*/
// #define Square(x) (x*x);
#define Value 20
// MultiLine Macros
#define MultiLine(x) for(int i=0;i<x;i+=1)   \
                {                            \
cout<<i<<" ";                                \
                };

class A{
public:
  inline virtual int f(){
    // C++ compiler cannot inline the virtual function. The reason is that the calls to a virtual function are resolved at runtime instead of compile time. Virtual means waiting until runtime, and inline means during compilation.
    return 0;
  }
};

// Inline namespace allow to access the variable or function without scope resoluting operator
// inline namespace STD{
//     int b=20;
//     class B{
//       int a=3;
//       public:
//       void Print(){
//         cout<<"B"<<endl;
//       }
//     };
//     class B1{
//       int a=3;
//       public:
//       void Print1(){
//         cout<<"B1"<<endl;
//       }
//     };
// }

// Anonymous namespace
// namespace{
//     int val=20;
// }
// using namespace STD;

class B{
  public:
  static const int a=20;
  static void f(){
    cout<<a<<endl;
  }
};
int main(){
    // int a=Square(5);
    // cout<<a<<endl;
    // MultiLine(Value);
    // B * b = new B();
    // b->Print();
    // cout<<val<<endl;

    // B::f();
    // B *b = new B();
    // b->f();
    

    // Alias
    // using a = int;
    // int c=20;
    // a * b=&c;
    // cout<<b<<endl;

    // assert(2>3 && "No active connections to send to, call connect with sucess" );
    
    map<int,int>mp;
    mp.emplace(1,2);
    auto pair = mp.emplace(1,2);
    cout<<pair.first->first<<" "<<pair.first->second<<" "<<pair.second<<endl;
    for(auto x:mp){
      cout<<x.first<<" "<<x.second<<endl;
    }
    return 0;
}
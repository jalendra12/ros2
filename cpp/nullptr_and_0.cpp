#include<iostream>
#include <typeinfo>
using namespace std;
// void fun(long long a){
//     cout<<"long long "<<a<<endl;
// }
// void fun(int a){
//     cout<<"int "<<a<<endl;
// }

// void fun(void){
//     cout<<"Void is called"<<endl;
// }
template<typename T>
void fun(T a){
    cout<<a<<endl;
}
int main(){
    // auto a = NULL; // 0(long long)
    int *p = NULL; // NULL is just 0, used to initialize a pointer
    // cout<<"nullptr is of type "<<typeid(a).name()<<endl;
    fun(1);
    fun(NULL); // this is fine(since NULL is 0L type) 
    fun(nullptr); // this is not fine
    return 0;
}
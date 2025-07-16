#include<iostream>
#include<functional>
using namespace std;
class A{
    public:
    void f1(){
        cout<<"f1"<<endl;
    }
};
void f2(auto f1){
    cout<<"f2"<<endl;
    f1();
}
int main(){
    //1. using Lambda function
    A a;
    f2([&](){
     a.f1();
    });

    //2. using bind
    f2(bind(&A::f1, &a));
    return 0;
}
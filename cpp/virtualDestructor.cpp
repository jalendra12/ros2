#include<iostream>
using namespace std;
class A{
public:
    A(){
        cout<<"A()"<<endl;
    }
    virtual~A(){
        cout<<"~A()"<<endl;
    }
};
class B:public A{
public:
    B(){
        cout<<"B()"<<endl;
    }
    virtual~B(){
        cout<<"~B()"<<endl;
    }
};
/*
When you delete an object through a base class pointer, without a virtual destructor, only the base class destructor will be called, and the destructor of the derived class will not be executed. 
This can lead to resource leaks (e.g., memory, file handles, network connections) or undefined behavior, especially if the derived class has dynamically allocated resources that need to be cleaned up properly.
*/
int main(){
    A *a = new B();
    delete a;
    return 0;
}
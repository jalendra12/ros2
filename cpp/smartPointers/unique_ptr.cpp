#include<iostream>
#include<memory>
using namespace std;
class A{
    int a;
public:
    A():a(20){
        cout<<"Object Created"<<endl;
    }
    A(A&a){
        cout<<"Copy Constructor"<<endl;
    }
    void Print(){
        cout<<"Printing..."<<a<<endl;
    }
    void print(){
        cout<<"Printing..."<<endl;
    }
};
int main(){
    unique_ptr<A>ptr{new A()};
    // unique_ptr<A>ptr1 = move(ptr); // move will pass ownership from ptr -> ptr1
    // ptr->print(); // this is not giving error because ptr has methods of class but doesnt have access to the resources like value of a
    // ptr->Print();

    // Converting unique ptr to shared ptr
    shared_ptr<A>ptr2 = move(ptr);
    
    return 0;
}
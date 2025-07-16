#include<bits/stdc++.h>
using namespace std;

class A;

class B{
    public:
    void Print(shared_ptr<A>&p1);
};
class A{
    private:
    int a=20;
    protected:
    int b=25;
    public:

    void print(){
        cout<<a<<endl;
    }
    // friend class B;
    // friend void func(shared_ptr<A>&ptr);
    // friend void B::Print(shared_ptr<A>&);
    // friend void fun1(shared_ptr<C>&);
};

// void func(shared_ptr<A>&ptr){
//     cout<<ptr->a<<endl;
// }

// void B::Print(shared_ptr<A>&p1){
//     cout<<p1->a<<endl;
// }


class C:public A{
    int c=30;
public:
    void P(){
        cout<<c<<endl;
    }
    friend void fun1(C&c1);
};

void fun1(C&c1){
    // only public & protected data members are accessable
    cout<<c1.c<<" "<<c1.b<<endl;
}


int main(){
    /*
    Three Types of friend functions
    1. friend class
    2. friend function
    3. friend function of different class
    */
    shared_ptr<A>ptr = make_shared<A>();
    shared_ptr<B>ptr1 = make_shared<B>();
    shared_ptr<C>ptr2 = make_shared<C>();
    // ptr2->P();
    // ptr->print();
    // ptr1->Print(ptr);
    // func(ptr);
    // ptr1->Print(ptr);
    C c1;
    fun1(c1);
    //Friendship is not inherited. In layman's terms, if a base class has a friend function, then the function doesn’t become a friend of the derived class
    return 0;
}
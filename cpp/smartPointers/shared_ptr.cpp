#include<iostream>
#include<memory>
using namespace std;
class B;
class A{
    public:
    shared_ptr<B>bptr;
    ~A(){
        cout<<"Deleted A()"<<endl;
    }
};
class B{
    public:
    // weak_ptr<A>aptr; // USE OF WEAK_PTR  
    shared_ptr<A>aptr;
    ~B(){
        cout<<"Deleted B()"<<endl;
    }
};
int main(){
    // int *a = new int{2};
    // int *b = new int{4};
    // shared_ptr<int>ptr1{a};
    // shared_ptr<int>ptr2{b};
    // // ptr1 = shared_ptr<int>{b}; // This will give an error because a is not managed by any pointers which leeds to undwfined behavours

    
    shared_ptr<A>ptr1{new A()};
    shared_ptr<B>ptr2{new B()};

    // Destructor will not get called, when the below both line are working, signifying a memory leakage
    ptr1->bptr=ptr2;
    ptr2->aptr=ptr1;

    ptr1->bptr.reset(); // can be resolved by breaking the cycle
   
    /*                  OR                    */

    /*!
    * \brief resolve using weak_ptr
    */

    shared_ptr<A> newA = make_shared<A>();
    shared_ptr<B> newB = make_shared<B>();
    newA->bptr = newB;
    newB->aptr = newA;

    cout<<ptr1.use_count()<<endl; 
    return 0;
}
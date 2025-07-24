#include<iostream>
#include<memory>
#include<atomic>
using namespace std;
// template<typename T>
class A{
int val;
public:
   A():val(0){}

   A(int v):val(v){
    cout<<"Object Created"<<endl;
   }

   // Move constructor
    A(A&& other) noexcept {
        cout << "Move Constructor" << endl;
        val = other.val;  // Transfer ownership of the resource
        other.val = /*nullptr*/0;    //  to indicate that the object no longer owns the resource.
    }
   A(A&a){
    cout<<"Copy Constructor"<<endl;
   }

   A(A*a){
    cout<<"Copy Constructor for Pointer"<<endl;
   }
   A(initializer_list<int> l){
    // This constructor is used when using list of values
    for(auto x:l)cout<<x<<" ";cout<<endl;
   }

   A& operator=(A&a){
    cout<<"Assignment"<<endl;
    return a;
   }

   A* operator=(A*a){
    cout<<"Assignmentp"<<endl;
    return a;
   }

   A& operator+(A&a){
    cout<<"Plus"<<endl;
    a.val += val;
    return a;
   }

   A&operator-(A&a){
    cout<<"Minus"<<endl;
    a.val = val-a.val;
    return a;
   }
   
   void fun()&{
    cout<<"lvalue function is called"<<endl;
   }
   void fun()&&{
    cout<<"rvalue function is called"<<endl;
   }
};
class Base {
public:
    virtual void mf1() const;
    virtual void mf2(int x);
    virtual void mf3() &;
    void mf4() const;
};
class Derived: public Base {
public:
    virtual void mf1()/*override*/; // we cant write override here because mf1(base) and mf1(derived) are not the same
    virtual void mf2(unsigned int x);
    virtual void mf3() &&;
    void mf4() const;
};

int main(){
    // A * aa = new A(5); // Allocation new memory
    // A * bb = new A(2);
 
    // bb = aa; // now pointer bb is pointing to aa
    // A &p = *bb; // This creates a reference (p) to the object that bb points to
    // A * cc = new A(bb); // This creates a new object on the heap by copying the object that bb points to.(deep copy)
    // A * ccc = new A(p); // This creates a new object on the heap by copying the object referred to by the reference p.(deep copy)

    /*
    The copy constructor is invoked during the initialization of a new object, whereas the assignment operator is invoked when an object is assigned to another already-existing object.
    */
    // A a(2),b(1);
    // b = a; // assignment operator invoked

    // // copy constructor
    // A c = b;
    // A d = {c};
    // A e(a);
    
    // int val(2);    // direct initialization
    // int val1{2};   // list initialization
    // int val2 = {2};// uniform initialization
    // cout<<val1<<endl;

    /* Atomic Variable cant be initialized with assignment */
    // atomic<int>val(0);
    // atomic<int>val{0};

    // atomic<int>val=20; // This will give error in C++11 but not in C++17

    // A a();// In C++, the syntax A a(); is interpreted as a function declaration 
    // A a = A(); // This is will work

    /* Move : Move semantics allow the ownership of resources (e.g., dynamically allocated memory, file handles, etc.) to be transferred from one object to another without copying the resource itself.*/
    // A a(2);
    // A b{std::move(a)};
    // A b{a};
    // A aa={"1","2","3"};

    // double d=8.284939;
    // int a{d}; // warning: narrowing conversion of ‘d’ from ‘double’ to ‘int’
    // cout<<a<<endl;

    A a;
    a.fun();   // a is lvalue

    A().fun(); // A() is a rvalue


    // Derived d;
    // d.mf3(); // error because d is lvalue

    int a1=20;
    int *p = &a1;
    cout<<p<<endl;
    int *p1 = move(p);
    cout<<p1<<endl;
    cout<<*p<<endl;
    return 0;
}
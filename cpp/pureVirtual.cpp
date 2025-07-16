#include<bits/stdc++.h>
using namespace std;
// A class is abstract if it has at least one pure virtual function.
class Base{
  public:
  virtual void func()=0;// pure virtual function
};
class D:public Base{
  public:
//   void func(){
//     cout<<"Hello"<<endl;
//   }
};
int main(){
    //1.  Error: Cannot instantiate an abstract class
        // Base b;
    //2. We can have pointers and references of abstract class type.
        // shared_ptr<Base>ptr = make_shared<D>();
        // ptr->func();
            // or
        // Base * ptr = new D();
        // ptr->func();
    //3. If we do not override the pure virtual function in the derived class, then the derived class also becomes an abstract class.
        // D d;//by remvoving overidden function this will throw error
    //4. An abstract class can have constructors. 
    //5. An abstract class in C++ can also be defined using struct keyword.
        /*
        struct shapeClass
        {
            virtual void Draw()=0;
        }
        */
    //6. Interface: An interface does not have an implementation of any of its methods, it can be considered as a collection of method declarations. In C++, an interface can be simulated by making all methods pure virtual.
    return 0;
}
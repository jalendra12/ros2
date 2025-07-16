#include<iostream>
#include<memory>
#include<string>
using namespace std;

/*
class B{
  public:
  void print1(){
    cout<<"B is called"<<endl;
  }
};
namespace demo
{
  class A:public B{
    int a;
    public:
    A(int a){
      this->a = a;
      cout<<a<<endl;
    }
    void print(){
      cout<<"A is called"<<endl;
    }
  };
}
int main(){
  // auto Node = make_shared<demo::A>(4);
  // Node->print1();

  auto Node = shared_ptr<demo::A>(new demo::A(4));
  Node->print1();
  return 0;
}
*/

// #include "class1.hpp"
// int main(){
//   auto ptr = make_shared<A>();
//   ptr->Print();
// }

// int main(int argc, char* argv[]) {
//   cout << "Argument count: " << argc << endl;
//   for (int i = 0; i < argc; ++i) {
//       cout << "Argument " << i << ": " << argv[i] << endl;
//   }
//   return 0;
// }

// g++ demo.cpp -o demo && ./demo 1 2 3(to pass value to main function)

// Inheritance
// class A{
//   string name;
//   public:
//   A(const string &name){
//     this->name = name;
//   }
// };
// class B:public A{
//   int a1,a2;
//   public:
//   B(int v1,int v2):A("Jalendra"),a1(v1),a2(v2){

//   }
//   void print(){
//     cout<<a1<<" "<<a2<<endl;
//   }
// };
// int main(){
//   // B *p1 = new B();
//   shared_ptr<B>p1 = make_shared<B>(1,2);
//   p1->print();
// }
int main(){
  int n1=10;
  auto fun = [&](int n){
    int sum=0;
    cout<<n1<<endl;
    for(int i=1;i<=n;i+=1)sum += i;
    return sum;
  };
  cout<<fun(10)<<endl;


  // thread t1();
  // thread t2();
  // for(int i=0;i<10;i+=1){
  //   if(i%2==0){
  //     this_thread::sleep_for(1s);
  //   }else{

  //   }
  // }
  // t1.join();
  // t2.join();
}
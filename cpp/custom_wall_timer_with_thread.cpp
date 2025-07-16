#include<bits/stdc++.h>
using namespace std;
class A{
  thread t;
  void callbacks(){
    int f=0;
    while(1){
      cout<<f<<endl;
      if(f){
        this_thread::sleep_for(1s);
        f=0;
      }else{
        this_thread::sleep_for(2s);
        f=1;
      }
    }
  }
  public:
  A(){
    t = thread(&A::callbacks,this);
  }
  ~A(){
    if(t.joinable()){
      t.join();
    }
  }
};
int main(){
  shared_ptr<A>ptr = make_shared<A>();
  return 0;
}
#include<iostream>
// Template Definition
template<typename T, typename S>
struct sp{
  sp(){
    std::cout<<"Template Definition"<<std::endl;
  }
};

// Partial Specialization
template<typename S>
struct sp<int,S>{
  sp(){
    std::cout<<"Partial Specialization"<<std::endl;
  }
};

// Full Specialization
template<>
struct sp<int,int>{
  sp(){
    std::cout<<"Full Specialization"<<std::endl;
  }
  constexpr int power(const int a,const int b){
    if(b<=0)return 1;
    return a*power(a,b-1);
  }
};


int main(){
    sp<int,int>sp1;
    const int val = sp1.power(4,10); // The val is calculated in compile-time, we should only store the value, if we try to console, then it will get executed in runtime
    // sp<std::string,int>sp2;
    // sp<int,float>sp3;
    return 0;
}
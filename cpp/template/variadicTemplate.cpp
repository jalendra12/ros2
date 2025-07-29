#include<iostream>

template<typename T>
void print1(T t){
    std::cout<<t<<std::endl;
}
template<typename T, typename ... T0>
void print1(T t, T0... rest){
    std::cout<<t<<std::endl;
    print1(rest...);
}


int main(){
    print1(1,2,"hello", 2.5f);
    return 0;
}
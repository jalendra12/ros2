#include<iostream>
#include<thread>
#include<mutex>
#include<vector>
template<typename T>
class thread_safe{
    public:
    stack<T>st;
    mutex m;
    thread_safe(){}
    thread_safe(const thread_safe&other){
        other.m.lock();
    }
};
int main(){
    std::thread t1(func);
    std::thread t2(func);
    t1.join();
    t2.join();
    std::cout<<count<<std::endl;
    return 0;
}
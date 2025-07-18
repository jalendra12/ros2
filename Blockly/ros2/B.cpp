#include<iostream>
#include<thread>
#include "A.h"
using namespace std;
class B{
    int c;
public:
    void f(){
        
    }
};
int main(){
    A *a = new A();
    std::thread t(&A::fun,a);
    t.join();
    return 0;
}
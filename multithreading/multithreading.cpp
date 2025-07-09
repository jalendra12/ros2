#include<iostream>
#include<thread>
using namespace std;
// thread thread_name(callable)
void func1(int n){
    cout<<n<<endl;
}
class func3 {
public:
    int n;
    func3(int a) : n(a) {}

    // Overload the operator() to 
    // make it callable
    void operator()() const {
        cout << n << endl;
    }
};
class MyClass {
public:
    // Non-static member function
    void f1(int num) {
        cout << num << endl;
    }

    // Static member function that takes one parameter
    static void f2(int num) {
        cout << num << endl;
    }
};
int main(){
    // In CPP Callable can be divided into 4 categories
        // 1. Function Pointer
        thread t(func1, 4);
        t.join();

        // 2. Lambda Expression
        thread t1([](int n){
            cout<<n<<endl;
        },30);
        t1.join();

        // 3. Function Object
        thread t2(func3(4));
        t2.join();

        // 4. Non-Static and Static Member Function
        MyClass obj;
        
        thread t3(&MyClass::f1, &obj, 3);
        t3.join();

        thread t4(&MyClass::f2, 7);
        t4.join();

    return 0;
}
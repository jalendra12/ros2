#include<iostream>
#include<semaphore>
#include<thread>
using namespace std;
int cnt = 0;
counting_semaphore<2>sem(2);
// binary_semaphore sem(1);
/*
counting_semaphore<t>sem(k);
 - Only k thread can access the critical section at a time at first, because the semaphore starts with k available permit.
 - Threads will be executed sequentially, with a maximum of t threads running concurrently at any point.
*/
void fun(int a){
    sem.acquire();
    cout<<"Func "<<a<<endl;
    this_thread::sleep_for(5s);
    sem.release();
}
void fun1(int a){
    sem.acquire();
    cout<<"Func1 "<<a<<endl;
    this_thread::sleep_for(10s);
    sem.release();
}
int main(){
    // counting_semaphore<1>sem(1);
        // counting_semaphore<resource>sem(key)
    //1.
        // sem.acquire();
        // this_thread::sleep_for(2s);
        // sem.release();
        //The acquire method decreases the semaphore count by one, effectively locking it. The release method increases the count, releasing the semaphore.
    //2. Try-Acquire
        // if(sem.try_acquire()){
            // sem.release();
            // }else{
            // cout<<"Semaphore was not acquired"<<endl;
        // }
    //3. Waiting with Timeout - C++20 also introduced the try_acquire_for and try_acquire_until methods to try acquiring the semaphore with a timeout.
        // if (sem.try_acquire_for(std::chrono::seconds(1))) {
        //     // Successfully acquired the semaphore within 1 second
        //     // Critical section code
        //     sem.release();
        // } else {
        //     // Semaphore was not acquired within 1 second
        // }
    
    // THERE ARE TWO TYPES OF SEMAPHORES
    /*
        1. std::counting_semaphore
          A counting semaphore is a synchronization primitive that allows multiple threads to access a shared resource up to a certain limit.
        2. std::binary_semaphore
          A binary semaphore is a simpler version of a semaphore that can have only two values: 0 and 1.
    */
    thread t1(fun1,1);
    thread t2(fun,2);
    thread t3(fun1,3);
    thread t4(fun,4);
    thread t5(fun,5);
    t1.join();
    t2.join();
    t3.join();
    t4.join();
    t5.join();
        
    return 0;
}
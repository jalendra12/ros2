#include<bits/stdc++.h>
using namespace std;
// Race condition(when two thread wants to access the common data at same time)

vector<int>v;
// 1. Using : Mutex(Mutual Exclusion) -- The most basic and common method to avoid race conditions is the use of mutexes
#include <mutex>
std::mutex mtx;

// 2. Instead of manually locking and unlocking the mutex, the std::lock_guard provides automatic locking and unlocking when the scope is exited, which reduces the risk of errors such as forgetting to unlock a mutex.
 
// 3. std::unique_lock is similar to std::lock_guard, but it provides more flexibility, such as manual unlocking and re-locking.

// 4. A shared_mutex allows multiple threads to read the shared resource concurrently, but ensures exclusive access for a thread that wants to modify the resource.
#include <shared_mutex>
std::shared_mutex smtx;

// 5. For certain types of shared variables (typically simple types like integers), you can use atomic operations, which ensure that the variable is updated in an indivisible manner without requiring explicit locks. This is often faster than using a mutex because it avoids the overhead of locking and unlocking.
#include <atomic>
atomic<int>counter(0);

// 6. If each thread needs to have its own copy of a variable (thus avoiding sharing altogether), you can use thread-local storage.
    // thread_local int counter = 0;

// 7. Condition Variables: Condition variables allow threads to wait for certain conditions to be met before proceeding. This is useful when you want to synchronize threads based on specific conditions (such as when a resource becomes available).
#include <condition_variable>
condition_variable cv;
bool ready = false;

//8. Locks with std::lock (Deadlock Prevention): If you have multiple mutexes that need to be locked in different parts of your program, there's a potential for deadlocks (where each thread waits for the other to release a mutex). To prevent this, you can use std::lock, which locks multiple mutexes in a deadlock-free way.

int main(){
    //1. Using : Mutex(Mutual Exclusion)
        // thread T1([=](){
        //     for(int i=1;i<=10000;i+=1){
        //         mtx.lock();
        //         v.push_back(i);
        //         mtx.unlock();
        //     }
        // });
        // thread T2([=](){
        //     for(int i=1;i<=10000;i+=1){
        //         mtx.lock();
        //         v.push_back(i);
        //         mtx.unlock();
        //     }
        // });
    //2. lock_guard
        // thread T1([=](){
        //     for(int i=1;i<=10000;i+=1){
        //         lock_guard<mutex> lock(mtx);
        //         v.push_back(i);
        //     }
        // });
        // thread T2([=](){
        //     for(int i=1;i<=10000;i+=1){
        //         lock_guard<mutex> lock(mtx);
        //         v.push_back(i);
        //     }
        // });
    //3. unique_lock
        // thread T1([=](){
        //     for(int i=1;i<=10000;i+=1){
        //         unique_lock<mutex> lock(mtx);
        //         v.push_back(i);
        //     }
        // });
        // thread T2([=](){
        //     for(int i=1;i<=10000;i+=1){
        //         unique_lock<mutex> lock(mtx);
        //         v.push_back(i);
        //     }
        // });
    //4. shared_lock
        // only reading
        // thread T1([=](){
        //     for(int i=1;i<=10000;i+=1){
        //         // shared_lock<shared_mutex> lock(smtx);
        //         if(v.size())cout<<v.back()<<endl;
        //     }
        // });
        // // writing
        // thread T2([=](){
        //     for(int i=1;i<=10000;i+=1){
        //         // unique_lock<shared_mutex> lock(smtx);
        //         v.push_back(i);
        //     }
        // });
    //5 & 6.
        // thread T1([=](){
        //     for(int i=1;i<=10000;i+=1){
        //         ++counter;
        //     }
        // });
        // thread T2([=](){
        //     for(int i=1;i<=10000;i+=1){
        //         ++counter;
        //     }
        // });


// The problem with lock is BUSY WAITING
    // when t1 lock the resource, t2 waits this will affect CPU cycle(is implemented using some bool variable)
    // CPU Cycle is very important so we use condition variable method
    
    
    //7. Condition Variables
        // The condition variable itself doesn't "store" the condition or any data directly. It manages:
            // A queue of threads waiting on a certain condition.
            // The notification mechanism for waking up threads when the condition may have changed.
            // The actual data that the condition variable helps synchronize is usually stored in a shared variable, like ready, in our example
    
    // thread T1([]{
    //     this_thread::sleep_for(1s);
    //     lock_guard<mutex>lock(mtx);
    //     ready = true;
    //     cout<<"Data Produced"<<endl;
    //     cv.notify_all();
    // });
    // thread T2([]{
    //     unique_lock<mutex> lock(mtx);
    //     cv.wait(lock, [] { return ready; });
    //     cout<<"Data Consumed"<<endl;
    // });

    /* IN DETAIL
       {
            // Lock aquired
            std::unique_lock<std::mutex> lck(mtx);
        ​
            // Suspend the thread, release the lock,
            //   wait for notifications from other threads.
            cv.wait(lck, [] {
                return ready;
            });

            // When other thread calls notify:
            //   cv re-acquires the mutex and check the condition again.
            //     If met, wake up the thread, keep holdong the lock, and continue.
            //     If not met, **release** the lock, and suspend the thread until notified.
        ​
            // Equivalent to:
            while(!ready) {
                // Suspend the thread and release the lock
                cv.wait(lck);
                // When notified, re-acquire the lock
                //    so that the condition checking is atomic.
            }
        }

        What if the condition is met before wait/never met?
            Ans: The first wait call of the cv will not check the condition. It will suspend the thread, release the mutex, and wait for notification. Having the condition already met when calling wait is like calling the function without the condition predicate
            {
                std::unique_lock<std::mutex> lck(mtx);
                // After calling wait, release the lock, suspend the thread, and wait for notification.
                cv.wait(lck);
            }
        What if notify() is called before wait/never called?
            If the notification is never called (and the conditions are met), it does not mean the thread will never wake up. There are two possibilities:
                1. Timeout Expire: If you use wait_for or wait_until, cv will wake up the thread after the timeout expires despite the condition not being met, and return false so you can handle timeout cases:
                2. Spurious Wakeup: By definition, a spurious wakeup is a situation where the conditional variable wakes up without being notified

        Suspend vs. Block
            Throughout this article, I have been using the term "suspend" to describe the behavior of a thread when it calls cv.wait instead of "block". 
            I prefer to use "suspend" because it better describes the behavior of this wait. When a thread is suspended, it does not consume any CPU time until the cv is signaled (as long as built with -pthread flag in Linux systems). 
            The thread is now unscheduled with its ID inserted at the tail of a list of waiting threads. In contrast, "blocking" a thread implies that the thread is performing some operation that is preventing it from running through, such as contention for a lock or waiting for I/O, which consumes more CPU resources. 
            For example, a do-while loop can be considered as blocking the thread
                do {
                    // Busy waiting for the condition, blocking the thread.
                } while (!ready);
    */

    T1.join();
    T2.join();
}
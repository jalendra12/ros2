#include<bits/stdc++.h>
using namespace std;
void func(){
    for(int i=1;i<=5;i+=1){
        this_thread::sleep_for(1s);
        cout<<i<<" ";
    }
    cout<<endl;
}
int main(){
    thread t(func);
    //1. t.join(), the main function wait till the t thread complete its execution

    //2. t.detach(), Allows the thread to run independently of the main thread
    // this_thread::sleep_for(3s); //wait for t thread to finish

    //3. t.get_id(); // this will return the unique ID of the thread
    t.join();
    return 0;
}
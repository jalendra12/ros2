#include<iostream>
using namespace std;
enum Days{
    Sunday=3,
    Monday=2,
    Tuesday=1,
};
enum class Day1{
    Sunday=3,
    Monday=2,
    Tuesday=1,
};
int main(){
    Days day = Sunday;
    cout<<day<<endl;

    Day1 day1 = Day1::Tuesday;
    if(day1 == Day1::Tuesday){
        cout<<"Hello"<<endl;
    }
    cout<<static_cast<int>(day1)<<endl;
    /*
    Internally, the enum class values are typically stored as integers (default is usually int), but you cannot directly access the integer representation unless you explicitly cast the enumerator to an integer.
    */
    return 0;
}
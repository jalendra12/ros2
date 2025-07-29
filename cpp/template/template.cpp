#include<iostream>
using namespace std;
#include<string>
// Function Template
// template<typename T>
// T add(T a, T b){
//     return a+b;
// }

// // Class Template
// template<typename T>
// class Add{
// public:
//  T add(T a, T b){
//     return a+b;
//  }
// };

// // Template Specilization
// template <typename T>
// class Printer {
// public:
//     void print(T data) {
//         cout << data << endl;
//     }
// };

// // Specialization for char*
// template <>
// class Printer<char*> {
// public:
//     void print(char* data) {
//         cout << "String: " << data << endl;
//     }
// };

// // non-type template parameters
// // Templates can accept values (not just types).

// template <typename T, int size,int val>
// class Array {
// private:
//     T arr[size]={val};
// public:
//     T& operator[](int index) { 
//         return arr[index]; 
//     }
// };

int main(){
    //1
    // string s1="1",s2="2";
    // cout<<add(s1,s2)<<endl;
    // cout<<add<int>(1,2)<<endl;

    // //2
    // Add<int>add;
    // cout<<add.add(2,3)<<endl;

    // //3
    // Printer<char*>prt;
    // prt.print((char*)"Hello"); // this will call specialized template
    // Printer<int>ptr1;
    // ptr1.print(20);

    // //4
    // Array<int,20,10>ar;
    // cout<<ar[0]<<endl;
    return 0;
}
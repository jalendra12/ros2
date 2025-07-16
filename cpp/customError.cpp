#include<bits/stdc++.h>
using namespace std;
// class exception {
// public:

//     exception() noexcept;
//     exception(const exception&) noexcept;
//     exception& operator=(const exception&) noexcept;
    
//     virtual ~exception();
//     virtual const char* what() const noexcept;
// };
class customError:public exception{
    public:
    const char* what() const noexcept override {
        return "This is a custom exception!";
    }
};
int main(){
    string error="Error";
    shared_ptr<customError>ptr = make_shared<customError>();
    return 0;
}
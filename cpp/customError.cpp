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
class custom{
    string message;
    public:
    custom():message(""){}
    custom(string s):message(s){}
    const string what() const noexcept{
        return message;
    }
};
int main(){
    // shared_ptr<customError>ptr = make_shared<customError>();
    // cout<<ptr->what()<<endl;

    // custom *cs = new custom("Error");
    // cout<<cs->what()<<endl;

    try{
        throw custom("E");
    }catch(custom &cm){
        cout<<cm.what()<<endl;
    }catch(...){
        cout<<"Default"<<endl;
    }
    return 0;
}
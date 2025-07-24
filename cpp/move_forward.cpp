#include<iostream>
#include<memory>
#include <type_traits>
#include<string>

using namespace std;

template<typename T>
remove_reference_t<T>&& move1(T&& input) {
    return static_cast<remove_reference_t<T>&&>(input);
}

class Int{
    int val;
public:
    Int(int a):val(a){
        cout<<"Created"<<endl;
    }

    Int(Int&& moved){
        cout<<"rvalue"<<endl;
    }
    Int& operator=(const Int& other) {
        cout << "Copy Assignment" << endl;
        return *this;
    }

    Int(Int& s){
        cout<<"Copy Called"<<endl;
    }
};


class Annotation {
public:
    Annotation(Int& text):value(move(text)){}
    Annotation(Int&& text):value(move(text)){}
private:
    Int value;
};




int main(){
    /*! \brief move and forward are merely functions (actually function templates) that perform casts.
               move unconditionally casts its argument to an rvalue, while
               forward performs this cast only if a particular condition is fulfilled.
    *   \param move does nothing but cast its argument to an rvalue, there have been suggestions that a better name for it might have been something like rvalue_cast. It does cast. It doesn’t move.
    */

    // int *p = new int{3};
    // int a=20;
    // shared_ptr<int>ptr = make_shared<int>(a);
    // shared_ptr<int>ptr1 = move(ptr);
    // cout<<ptr1.use_count()<<endl;
    // cout<<ptr.use_count()<<endl;


    // using T1 = int&;  // lvalue reference
    // using T2 = int&&; // rvalue reference
    // using T3 = int;   // non-reference type

    // cout << is_same<remove_reference<T1>::type, int>::value << "\n";
    // cout << is_same<remove_reference<T2>::type, int>::value << "\n";
    // cout << is_same<remove_reference<T3>::type, int>::value << "\n";

    // shared_ptr<int>ptr = make_shared<int>(2);
    // shared_ptr<int>ptr1 = move1(ptr);
    // cout<<ptr1.use_count()<<endl;
    // cout<<ptr.use_count()<<endl;

    // Int *s = new Int(2);
    // Int *s1 = new Int(3);
    // s1 = s;
    Int s(2),s1(4);
    // s1=s;
    Annotation obj(move(s));
    return 0;
}
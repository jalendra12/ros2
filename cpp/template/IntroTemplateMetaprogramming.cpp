#include<iostream>
/*
What is Metaprogramming?
Program : A computer program is a sequence or set of instructions in a programming language for a computer to execute.
Template metaprogramming in C++ is a programming technique where templates are used to perform computations at compile time, rather than at runtime.

*/

// how to check which data type using type_traits

// #include<type_traits>
//own is_pointer
// std::is_pointer<T>::value

// base
template<typename T>
struct is_pointer{
    static constexpr bool value = false;
};
// specialization
template<typename T>
struct is_pointer<T*>{
    static constexpr bool value = true;
};

// if we are not using constexpr then there will be a a jmp command in Assembly code(Ensuring that it ir running in runtime)
// std::is_floating_point<T>::value will only return true of T type is float, double long double
template<typename T>
struct strip_ptr{
    using type = T;
};
template<typename T>
struct strip_ptr<T*>{
   using type = T;
};

template<typename T>
struct typeName{
    void print(T t){
        using T_without_ptr = typename strip_ptr<T>::type;
        if constexpr(is_pointer<T>::value && std::is_floating_point<T_without_ptr>::value){
            std::cout<<*t<<std::endl;
        }else std::cout<<t<<std::endl;
    }
};

int main(){
    typeName<int*>tn;
    int a=20;
    int *b = &a;
    tn.print(b);

    float b1=30.3;
    float *c1 = &b1;
    typeName<float*>fp;
    fp.print(c1);

    return 0;
}
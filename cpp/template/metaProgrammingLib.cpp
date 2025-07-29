#include<iostream>
template<bool condition, typename THEN, typename ELSE>
struct if_{
    using type=THEN;
};

template<typename THEN, typename ELSE>
struct if_<true,THEN,ELSE>{
 using type=THEN;
};

template<typename THEN, typename ELSE>
struct if_<false,THEN,ELSE>{
 using type=ELSE;
};

int main(){
    std::cout << std::boolalpha << (std::is_same<int,if_<(5>5),int,float>::type>::value) << std::endl;
    return 0;
}
#include<iostream>
#include<tuple>
#include<vector>

// Run-Time Search
bool search(std::string s,std::vector<std::string>&v,int idx=0){
    if(idx>=v.size())return false;
    else return (v[idx]==s)?true:search(s,v,idx+1);
}
// if-else in template-metaprogramming
template<bool condition, typename THEN, typename ELSE>
struct if_{
using type = ELSE;
};

template<typename THEN, typename ELSE>
struct if_<true,THEN, ELSE>{
    using type = THEN;
};

template<typename THEN, typename ELSE>
struct if_<false, THEN, ELSE>{
    using type = ELSE;
};

// Compile-Time Search
// template<typename s,typename v,int idx>
// struct contain_type:
//     if_<
//       std::is_same<std::tuple_element_t<idx, v>,s>::value,
//       std::true_type,
//       typename if_<
//           (idx >= std::tuple_size<v>::value),std::false_type,contain_type<s,v,idx+1>
//       >::type
//     >::type
// {};

template<typename s,typename v,int idx=0>
struct contain_type1:
    if_< (idx >= std::tuple_size<v>::value),std::false_type,

    typename if_<std::is_same<std::tuple_element_t<idx, v>,s>::value, std::true_type, contain_type1<s,v,idx+1>
                >::type
      >::type
{};

// factorial 
template<int n>
struct factorial{
    static constexpr int value = n*factorial<n-1>::value;
};
// base case
template<>
struct factorial<0>{
    static constexpr int value = 1;
};

int main(){
    // std::tuple<int,bool,float>t;
    // t = {1,true,1.5};
    // std::cout<<std::get<2>(t)<<std::endl;
    std::vector<std::string>v{"Hello","Hello1","Hello2"};

    std::cout<<search("Hello",v,0)<<std::endl;
    std::cout << std::boolalpha << (std::is_same<int,if_<(5>5),int,float>::type>::value) << std::endl;

    std::tuple<bool, float, double, char>tup;
    // constexpr bool found = contain_type1<int, decltype(tup), 0>::value;

    std::cout << std::boolalpha << (contain_type1<char, decltype(tup)>::value) <<std::endl;
    constexpr int val = factorial<12>::value;
    std::cout<<val<<std::endl;
    return 0;
}
#include<iostream>
#include <type_traits>

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

template<typename T>
struct dimension : std::integral_constant<int, 0> {};

template<typename T, std::size_t N>
struct dimension<T[N]> : std::integral_constant<int, 1 + dimension<T>::value> {};

int main(){
    using arr_type = int[1][1][1][1][2];

    constexpr int val = dimension<arr_type>::value;

    std::cout << "Dimension of array: " << val << std::endl;

    return 0;
}
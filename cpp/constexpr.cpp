#include <iostream>
using namespace std;
constexpr int por(const int a,const int b){
    if(b<=0)return 1;
    return a*por(a,b-1);
}
class Por{
    int x,y;
public:
    constexpr Por(const int a,const int b):x(a),y(b*b){}
};
int main() {
    const int val=por(20,3);
    const int val1=por(30,3);
    // Por a(2,6); // Object is created during compile time
    // cout<<val<<endl;
}



/*
How to visualize constexpr

command : g++ -S -o assembly.s constexpr.cpp
  The above command will generate a assembly file which does not contsins multiplication, that means the mul operation is done during compile-time

This is assembly code of function without constexpr

_Z3porii:
.LFB1731:
    .cfi_startproc
    endbr64
    pushq   %rbp
    .cfi_def_cfa_offset 16
    .cfi_offset 6, -16
    movq    %rsp, %rbp
    .cfi_def_cfa_register 6
    movl    %edi, -20(%rbp)     ; Store the first argument (a) into local variable
    movl    %esi, -24(%rbp)     ; Store the second argument (b) into local variable
    movl    -20(%rbp), %eax     ; Move the value of 'a' (from -20(%rbp)) into eax
    imull   -24(%rbp), %eax     ; Multiply 'a' (in eax) by 'b' (from -24(%rbp)) and store in eax
    movl    %eax, -8(%rbp)      ; Store the result (a * b) in memory at -8(%rbp)
    movl    -8(%rbp), %eax      ; Move the result (a * b) into eax
    imull   -20(%rbp), %eax     ; Multiply the result (a * b) by 'a' again
    movl    %eax, %edx          ; Store the result of (a * b) * a in edx
    movl    -24(%rbp), %eax     ; Move the value of 'b' into eax
    addl    %edx, %eax          ; Add the value of (a * b) * a to b (the result of the second multiplication)
    movl    %eax, -4(%rbp)      ; Store the final result (a * b + a * b) into memory at -4(%rbp)
    movl    -4(%rbp), %eax      ; Move the final result into eax (return register)
    popq    %rbp
    .cfi_def_cfa 7, 8
    ret
    .cfi_endproc
.LFE1731:

The assembly code with constexpr will not have mul keyword, which signifies that multiplication is done during COMPILE TIME

*/
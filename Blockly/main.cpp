#include<iostream>
#include<string>
#include<memory>
#include "Blocks.hpp"
Base * Create(){
    Base * n1 = new Print();
    Base * n2 = new Repeat(2);
    Base * n3 = new Move();

    n1->next_block = n2;
    n2->next_block = n3;

    Base * h1 = new Print();
    Base * h2 = new Move();
    h1->next_block = h2;

    n2->child_block = h1;
    return n1;
}
void Iterate(Base*head){
    if(!head)return;
    if(head->nodeName=="print"){
        std::cout<<"Print"<<std::endl;
    }else if(head->nodeName=="move"){
        std::cout<<"Move"<<std::endl;
    }else{
        head->repeat(Iterate);
    }
    Iterate(head->next_block);
}


int main(){
    Base * head = NULL;
    try{
        head = Create();
    }catch(exception &ex){
        std::cout<<ex.what()<<std::endl;
    }

    Iterate(head);

    return 0;
}
#include<iostream>
#include<functional>
#include<string>
#include "Base.hpp"
using namespace std;

class Print:public Base{
    std::string message;
public:
    Print():Base("print"),message(""){}
    Print(std::string s):Base("print"),message(s){}

    void setMessage(std::string s){
        this->message = s;
    }
    void print(){
        std::cout<<message<<std::endl;
    }
    virtual ~Print(){}
};


class Move:public Base{
public:
    Move():Base("move"){}

    void move(){
        std::cout<<"Moved"<<std::endl;
    }
    virtual ~Move(){}
};


class Repeat:public Base{
    int cnt;
public:
    Repeat():cnt(0){}
    Repeat(int count=0):Base("repeat"),cnt(count){
        
    }

    int getCount()const{
        return this->cnt;
    }

    void setCount(int count){
        this->cnt = count;
    }

    void repeat(function<void(Base*)> Iterate){
        std::cout<<"Repeating Start..."<<std::endl;
        if(this->cnt <= 0){
            while(1){
               this->child_block;
            }
        }else{
            for(int i=0;i<(this->cnt);i+=1){
                Iterate(this->child_block);
            }
        }
        std::cout<<"Repeating End..."<<std::endl;
    }
    virtual ~Repeat(){}
};
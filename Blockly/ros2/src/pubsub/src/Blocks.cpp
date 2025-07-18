#include<iostream>
#include<string>
#include "Base.h"
using namespace std;
class Print:public Base{
    std::string message;
public:
    Print():Base("print"),message(""){}
    Print(std::string s):Base("print"),message(s){}

    void setMessage(std::string s){
        this->message = s;
    }
    void block_function(){
        if(Base::refresh)return;
        while(Base::stop1 && rclcpp::ok()){
            std::cout<<"Stopped"<<std::endl;
            std::this_thread::sleep_for(1000ms);
        }

        std::cout<<message<<std::endl;
        std::this_thread::sleep_for(1000ms);

        // if(this->child_block){
        //     this->child_block->block_function();
        // }
        if(this->next_block){
            this->next_block->block_function();
        }
    }

    virtual ~Print(){
        std::cout<<"Print Deleted"<<std::endl;
    }
};


class Move:public Base{
    std::string message;
public:
    Move():Base("move"),message(""){}
    Move(std::string s):Base("move"),message(s){}

    void block_function(){
        if(Base::refresh)return;
        while(Base::stop1 && rclcpp::ok()){
            std::cout<<"Stopped"<<std::endl;
            std::this_thread::sleep_for(1000ms);
        }
        std::cout<<message<<std::endl;
        std::this_thread::sleep_for(1000ms);
        // if(this->child_block){
        //     this->child_block->block_function();
        // }
        if(this->next_block){
            this->next_block->block_function();
        }
    }

    virtual ~Move(){
        std::cout<<"Move Deleted"<<std::endl;
    }
};


class Repeat:public Base{
    public:
    int end;
    Repeat():end(0){}
    Repeat(int count=0):Base("repeat"),end(count){}

    void block_function(){
        if(Base::refresh)return;
        while(Base::stop1 && rclcpp::ok()){
            std::cout<<"Stopped"<<std::endl;
            std::this_thread::sleep_for(1000ms);
        }
        std::cout<<"Repeating Start..."<<std::endl;
        std::this_thread::sleep_for(1000ms);
        if(this->end < 0){
            while(Base::stop1 && rclcpp::ok()){
                std::cout<<"Invalid Count in Repeat Block..."<<std::endl;
                std::this_thread::sleep_for(1000ms);
            }
        }else{
            for(int i=0;i<(this->end);i+=1){
                if(this->child_block){
                    this->child_block->block_function();
                }
            }
        }

        std::cout<<"Repeating End..."<<std::endl;

        if(this->next_block){
            this->next_block->block_function();
        }
    }
    virtual ~Repeat(){
        std::cout<<"Repeat Deleted"<<std::endl;
    }
};
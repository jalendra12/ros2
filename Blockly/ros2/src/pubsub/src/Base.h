#ifndef Base_H
#define Base_H

#include<iostream>
#include<functional>
class Base{
public:
    std::string nodeName;
    Base * child_block = NULL;
    Base * next_block = NULL;
    static bool stop1, refresh;
    Base(std::string name):nodeName(name){}

    Base(){
        throw std::runtime_error("Node Name Required...");
    }

    virtual void block_function()=0;

    virtual ~Base(){
        std::cout<<"Base Deleted"<<std::endl;
    }
};
bool Base::stop1 = false;
bool Base::refresh = false;

#endif
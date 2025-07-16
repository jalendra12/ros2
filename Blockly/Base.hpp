#include<iostream>
#include<functional>
class Base{
public:
    std::string nodeName;
    Base * child_block = NULL;
    Base * next_block = NULL;
    Base(std::string name):nodeName(name){}

    Base(){
        throw std::runtime_error("Node Name Required...");
    }

    virtual void print(){}
    virtual void move(){}
    virtual void repeat(std::function<void(Base*)>f){}
    virtual int getCount(){
        return 0;
    }
};
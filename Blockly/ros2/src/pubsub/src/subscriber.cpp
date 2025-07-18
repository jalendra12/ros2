#include<iostream>
#include <functional>
#include <memory>
#include<stack>
#include<thread>
#include <atomic>

#include "rclcpp/rclcpp.hpp"
#include "message/msg/instruct_robot.hpp"

#include "Blocks.cpp"
using std::placeholders::_1;

Base * Create(){
    Base * n1 = new Print("print in main");
    Base * n2 = new Repeat(2);
    Base * n3 = new Move("move in main");

    n1->next_block = n2;
    n2->next_block = n3;

    Base * h1 = new Print(" print in repeat");
    Base * h2 = new Repeat(3);
    n2->child_block = h1;
    Base * h3 = new Move(" move in repeat");
    h1->next_block = h2;
    h2->next_block = h3;

    Base * h11 = new Print("  print in repeat");
    Base * h21 = new Move("  move in repeat");
    h11->next_block = h21;
    h2->child_block = h11;

    return n1;
}
class MinimalSubscriber : public rclcpp::Node
{
public:
  MinimalSubscriber()
  : Node("minimal_subscriber"),Start(NULL)
  {
    subscription_ = this->create_subscription<message::msg::InstructRobot>(
      "topic", 10, std::bind(&MinimalSubscriber::topic_callback, this, _1));
    Start = Create();
  }
  ~MinimalSubscriber(){
    if(t1.joinable())t1.join();

  }

private:
  void topic_callback(const message::msg::InstructRobot & msg)
  {
    std::cout<<msg.status<<std::endl;
    if(msg.status == 2){ // pause
      Base::stop1 = true;
      Base::refresh = false;
    }
    else if(msg.status == 1){ // start
      Base::stop1 = false;
      Base::refresh = true;
      if(t1.joinable())t1.join();
      Base::refresh = false;
      std::cout<<"Starting..."<<std::endl;
      t1 = std::thread(&Base::block_function, Start);
    }else if(msg.status==3){ // resume
      Base::stop1 = false;
      Base::refresh = false;
      if(t1.joinable())t1.join();
    }else{ //restart
      Base::stop1 = false;
      Base::refresh = true;
      if(t1.joinable())t1.join();
      t1 = std::thread(&Base::block_function, Start);
    }
  }
  rclcpp::Subscription<message::msg::InstructRobot>::SharedPtr subscription_;
  Base *Start;
  std::thread t1;
  std::stack<Base*>stackSpace;
};
/*
t1 = std::thread([&](){
  while(!stackSpace.empty())stackSpace.pop();

  stackSpace.push(Start);
  while(!stackSpace.empty() && rclcpp::ok()){
    while(Base::stop1 && rclcpp::ok()){
      std::cout<<"Stopped"<<std::endl;
      std::this_thread::sleep_for(1000ms);
    }

    Base * b = stackSpace.top();
    b->block_function();
    std::this_thread::sleep_for(500ms);
    stackSpace.pop();

    if(b->next_block)stackSpace.push(b->next_block);
    if(b->nodeName == "repeat"){
      for(int i=0;i<2;i+=1){
        if(b->child_block){
          stackSpace.push(b->child_block);
        }
      }
    }
  }
});
*/
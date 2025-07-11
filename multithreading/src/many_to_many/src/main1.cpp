#include <chrono>
#include <memory>
#include <string>
#include <functional>
#include "rclcpp/rclcpp.hpp"
#include "message/msg/thread_message.hpp"
using std::placeholders::_1;
using namespace std::chrono_literals;

class PS1:public rclcpp::Node{
    public:
    PS1():Node("node1"),X(60){
      publisher = this->create_publisher<message::msg::ThreadMessage>("topic", 10);
      timer_ = this->create_wall_timer(1s, std::bind(&PS1::timer_callback_publisher, this));

      subscription = this->create_subscription<message::msg::ThreadMessage>(
      "topic", 10, std::bind(&PS1::timer_callback_subscriber, this, _1));
    }

    private:
    rclcpp::Subscription<message::msg::ThreadMessage>::SharedPtr subscription;
    rclcpp::Publisher<message::msg::ThreadMessage>::SharedPtr publisher;
    rclcpp::TimerBase::SharedPtr timer_;
    int X;
    void timer_callback_publisher(){
        auto message = message::msg::ThreadMessage();
        message.v1 = 30;
        message.v2 = 1;
        std::cout<<"Publishing from 1..."<<std::endl;
        publisher->publish(message);
    }
    
    void timer_callback_subscriber(const message::msg::ThreadMessage &msg){
        std::cout<<"Subscriber 1 :";
        if(msg.v2 != 1){
            std::cout<<msg.v1<<" "<<msg.v2<<std::endl;
            if(msg.v1 == X){
                std::cout<<"Achieved"<<std::endl;
            }else{
                auto message = message::msg::ThreadMessage();
                message.v1 = msg.v1;
                message.v2 = 1;
                std::cout<<"Publishing from 1..."<<std::endl;
                publisher->publish(message);
            }
        }else{
            std::cout<<"Received data from same node"<<std::endl;
        }
    }
};

int main(int argc,char **argv){
    rclcpp::init(argc,argv);
    rclcpp::spin(std::make_shared<PS1>());
    rclcpp::shutdown();
    return 0;
}
#include <chrono>
#include <memory>
#include <string>
#include <functional>
#include "rclcpp/rclcpp.hpp"
#include "message/msg/thread_message.hpp"
using std::placeholders::_1;
using namespace std::chrono_literals;

class PS2:public rclcpp::Node{
    public:
    PS2():Node("node2"){
      publisher = this->create_publisher<message::msg::ThreadMessage>("topic", 10);
      timer_ = this->create_wall_timer(4s, std::bind(&PS2::timer_callback_publisher, this));

      subscription = this->create_subscription<message::msg::ThreadMessage>(
      "topic", 10, std::bind(&PS2::timer_callback_subscriber, this, _1));
    }

    private:
    rclcpp::Subscription<message::msg::ThreadMessage>::SharedPtr subscription;
    rclcpp::Publisher<message::msg::ThreadMessage>::SharedPtr publisher;
    rclcpp::TimerBase::SharedPtr timer_;
    void timer_callback_publisher(){
        // auto message = message::msg::ThreadMessage();
        // message.v1 = Y;
        // message.v2 = 1;
        // std::cout<<"Publishing from 2..."<<std::endl;
        // publisher->publish(message);
    }
    
    void timer_callback_subscriber(const message::msg::ThreadMessage &msg){
        std::cout<<"Subscriber 2"<<std::endl;
        if(msg.v2 != 2 && msg.v1 <= 60){
            std::cout<<"Received data from 1 :"<<msg.v1<<std::endl;
            auto message = message::msg::ThreadMessage();
            message.v1 = msg.v1+10;
            message.v2 = 2;
            std::cout<<"Publishing from 2..."<<std::endl;
            publisher->publish(message);
        }else{
            std::cout<<"Received data from same node"<<std::endl;
        }
    }
};

int main(int argc,char **argv){
    rclcpp::init(argc,argv);
    rclcpp::spin(std::make_shared<PS2>());
    rclcpp::shutdown();
    return 0;
}
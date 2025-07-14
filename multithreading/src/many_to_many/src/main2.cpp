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
    PS2():Node("node2"),y(-1){
      publisher = this->create_publisher<message::msg::ThreadMessage>("topic", 10);
    //   timer_ = this->create_wall_timer(2s, std::bind(&PS2::timer_callback_publisher, this));

      subscription = this->create_subscription<message::msg::ThreadMessage>(
      "topic", 10, std::bind(&PS2::timer_callback_subscriber, this, _1));
    }

    private:
    int y;
    int last_value = 0;
    rclcpp::Subscription<message::msg::ThreadMessage>::SharedPtr subscription;
    rclcpp::Publisher<message::msg::ThreadMessage>::SharedPtr publisher;
    rclcpp::TimerBase::SharedPtr timer_;
    void timer_callback_publisher(){
        auto message = message::msg::ThreadMessage();
        message.v1 = y;
        message.v2 = 2;
        publisher->publish(message);
    }
    
    void timer_callback_subscriber(const message::msg::ThreadMessage &msg){
        std::cout<<"Subscriber 2"<<std::endl;
        if(msg.v2 != 2 && msg.v1 <= 60 && last_value != y){
            std::cout<<"Received data from 1 :"<<msg.v1<<std::endl;
            auto message = message::msg::ThreadMessage();
            message.v1 = msg.v1+10;
            y = msg.v1+10;
            message.v2 = 2;
            last_value = msg.v1;
            std::cout<<"Publishing from 2..."<<std::endl;
            timer_callback_publisher();
        }
    }
};

int main(int argc,char **argv){
    rclcpp::init(argc,argv);
    rclcpp::spin(std::make_shared<PS2>());
    rclcpp::shutdown();
    return 0;
}
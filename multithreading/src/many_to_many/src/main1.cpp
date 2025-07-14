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
    PS1():Node("node1"),X(60),last_value(-1){
      publisher = this->create_publisher<message::msg::ThreadMessage>("topic", 10);
    //   timer_ = this->create_wall_timer(1s, std::bind(&PS1::timer_callback_publisher, this));
    
    subscription = this->create_subscription<message::msg::ThreadMessage>(
        "topic", 10, std::bind(&PS1::timer_callback_subscriber, this, _1));

    timer = std::thread(&PS1::timer_callback_publisher,this);// calling callback with different time interval

    }
    ~PS1(){
        if(timer.joinable()){
            timer.join();
        }
    }

    private:
    rclcpp::Subscription<message::msg::ThreadMessage>::SharedPtr subscription;
    rclcpp::Publisher<message::msg::ThreadMessage>::SharedPtr publisher;
    rclcpp::TimerBase::SharedPtr timer_;
    std::thread timer;
    int X,last_value;

    void timer_callback_publisher(){
        int f=1;
        while(rclcpp::ok()){
            auto message = message::msg::ThreadMessage();
            message.v1 = 30;
            message.v2 = 1;
            if(last_value != X){
                std::cout<<"Publishing from 1..."<<std::endl;
                last_value = message.v1;
                publisher->publish(message);

                if(f){
                    std::this_thread::sleep_for(1s);
                    f=0;
                }else{
                    std::this_thread::sleep_for(3s);
                    f=1;
                }
            }
        }
    }
    
    void timer_callback_subscriber(const message::msg::ThreadMessage &msg){
        if(last_value != msg.v1)
        {
            auto message = message::msg::ThreadMessage();
            message.v1 = msg.v1;
            message.v2 = 1;
            std::cout<<"Received data from 2 :"<<msg.v1<<std::endl;
            publisher->publish(message);
            last_value = msg.v1;
        }
    }
};

int main(int argc,char **argv){
    rclcpp::init(argc,argv);
    rclcpp::spin(std::make_shared<PS1>());
    rclcpp::shutdown();
    return 0;
}
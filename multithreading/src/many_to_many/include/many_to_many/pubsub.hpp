#include <chrono>
#include <functional>
#include <memory>
#include <string>

#include "rclcpp/rclcpp.hpp"
#include "message/msg/thread_message.hpp"
using std::placeholders::_1;

class PubSub:public rclcpp::Node{
    public:
    PubSub():Node("pubsub1"){
      publisher = this->create_publisher<message::msg::ThreadMessage>("topic", 10);
      timer_ = this->create_wall_timer(
      500ms, std::bind(&PubSub::timer_callback_publisher, this));

      subscription = this->create_subscription<message::msg::ThreadMessage>(
      "topic", 10, std::bind(&PubSub::timer_callback_subscriber, this, _1));
    }

    private:
    rclcpp::Subscription<message::msg::ThreadMessage>::SharedPtr subscription;
    rclcpp::Publisher<message::msg::ThreadMessage>::SharedPtr publisher;
    clcpp::TimerBase::SharedPtr timer_;

    void timer_callback_publisher(){
        auto message = message::msg::ThreadMessage();
        message.s1 = "pubsub11";
        message.s2 = "pubsub12";
        std::cout<<"Publishing..."<<std::endl;
        publisher.publish(message);
    }
    void timer_callback_subscriber(const message::msg::ThreadMessage &msg){
        cout<<msg->s1<<" "<<msg->s2<<endl;
    }
};
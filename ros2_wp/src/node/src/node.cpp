#include<iostream>
#include<string>
using namespace std;
#include "rclcpp/rclcpp.hpp"
#include "std_msgs/msg/string.hpp"
#include "tutorial_interfaces/srv/add_three_ints.hpp"

using std::placeholders::_1;

// Callable function for pub/sub
void f(const std_msgs::msg::String &s1){
    cout<<"Message: "<< s1.data <<endl;
}
// Callable function for serv/client
void f1(const shared_ptr<tutorial_interfaces::srv::AddThreeInts::Request> request,shared_ptr<tutorial_interfaces::srv::AddThreeInts::Response> response){
    response->sum = request->a + request->b + request->c;
    cout<<"Function Called"<<endl;
}

class Publisher1 : public rclcpp::Node{
    public:
    Publisher1():Node("Jalendra"){
        publisher = this->create_publisher<std_msgs::msg::String>("Topic",10);
        timer = this->create_wall_timer(1s, bind(&Publisher1::callback_function, this));
    }
    private:
    rclcpp::Publisher<std_msgs::msg::String>::SharedPtr publisher;
    rclcpp::TimerBase::SharedPtr timer;
    void callback_function(){
        auto message = std_msgs::msg::String();
        cout<<"Publishing Data"<<endl;
        message.data = "Hello";
        publisher->publish(message);
    }
};
class Subscriber1 : public rclcpp::Node{
    public:
    Subscriber1() : Node("Jalendra1"){
        subscription = this->create_subscription<std_msgs::msg::String>("Topic",10, bind(&Subscriber1::callback_function, this, _1));
    }
    private:
    rclcpp::Subscription<std_msgs::msg::String>::SharedPtr subscription;
    void callback_function(const std_msgs::msg::String & msg){
        cout<<msg.data.c_str()<<endl;
    }
};

int main(int argc,char*argv[]){
    rclcpp::init(argc,argv);
    /*
    // Manually Create a Node and Publisher Subscriber
        rclcpp::Node node = rclcpp::Node("J"); // Created a Node
        rclcpp::Node node1 = rclcpp::Node("J1");
        rclcpp::Publisher<std_msgs::msg::String>::SharedPtr publisher = node.create_publisher<std_msgs::msg::String>("Topic",10); // Node became publisher to the topic "Topic"
        rclcpp::Subscription<std_msgs::msg::String>::SharedPtr subscriber = node1.create_subscription<std_msgs::msg::String>("Topic",10,f); // Node became subscriber to the topic "Topic"
        rclcpp::Client<tutorial_interfaces::srv::AddThreeInts>::SharedPtr client = node.create_client<tutorial_interfaces::srv::AddThreeInts>("service");
        rclcpp::Service<tutorial_interfaces::srv::AddThreeInts>::SharedPtr server = node1.create_service<tutorial_interfaces::srv::AddThreeInts>("service", f1);
    */

    // rclcpp::spin(make_shared<Publisher1>());
    

    // thread t1([](){
    //     rclcpp::spin(make_shared<Publisher1>());
    // });

    // thread t2([](){
    //     rclcpp::spin(make_shared<Subscriber1>());
    // });
    // t1.join();
    // t2.join();


    // Client-Server Architecture

    shared_ptr<rclcpp::Node>node = rclcpp::Node::make_shared("client1");
    rclcpp::Client<tutorial_interfaces::srv::AddThreeInts>::SharedPtr client = node->create_client<tutorial_interfaces::srv::AddThreeInts>("Service");
    auto request = make_shared<tutorial_interfaces::srv::AddThreeInts::Request>();
    request->a = 1;
    request->b = 2;
    request->c = 3;

    
    shared_ptr<rclcpp::Node>node1 = rclcpp::Node::make_shared("server1");
    rclcpp::Service<tutorial_interfaces::srv::AddThreeInts>::SharedPtr server = node1->create_service<tutorial_interfaces::srv::AddThreeInts>("Service",f1);

    thread t2([=](){
        cout<<"Server is Ready"<<endl;
        rclcpp::spin(node1);
    });

    thread t1([=](){
        while(!client->wait_for_service(1s)){
            if (!rclcpp::ok()) {
            cout<<"Interupted"<<endl;
            return 0;
            }
            cout<<"Waiting Again"<<endl;
        }

        auto result = client->async_send_request(request);

        if (rclcpp::spin_until_future_complete(node, result) == rclcpp::FutureReturnCode::SUCCESS){
            cout<<result.get()->sum<<endl;
        } else {
            cout<<"Failed"<<endl;
        }
    });


    t1.join();
    t2.join();

    rclcpp::shutdown();
    return 0;
}
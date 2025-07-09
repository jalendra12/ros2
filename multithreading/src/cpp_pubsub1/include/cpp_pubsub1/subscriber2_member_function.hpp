#include <memory>

#include "rclcpp/rclcpp.hpp"
#include "std_msgs/msg/string.hpp"
using std::placeholders::_1;

class MinimalSubscriber2 : public rclcpp::Node
{
  public:
    MinimalSubscriber2()
    : Node("minimal_subscriber2")
    {
      subscription_ = this->create_subscription<std_msgs::msg::String>(
      "topic2", 10, std::bind(&MinimalSubscriber2::topic_callback, this, _1));
    }

  private:
    void topic_callback(const std_msgs::msg::String & msg) const
    {
        // std::this_thread::sleep_for(std::chrono::milliseconds(2000));
        auto now = std::chrono::system_clock::now();
        auto now_time_t = std::chrono::system_clock::to_time_t(now);
        auto duration = now.time_since_epoch();
        auto microseconds = std::chrono::duration_cast<std::chrono::microseconds>(duration).count();

        std::tm* local_time = std::localtime(&now_time_t);

        // Format minutes, seconds, and microseconds
        std::stringstream time_stream;
        time_stream << std::put_time(local_time, "%M:%S") << ":" << (microseconds % 1000000);
      RCLCPP_INFO(this->get_logger(), "[%s] I heard from 2: '%s'",time_stream.str().c_str(), msg.data.c_str());
    }
    rclcpp::Subscription<std_msgs::msg::String>::SharedPtr subscription_;
};

// int main(int argc, char * argv[])
// {
//   rclcpp::init(argc, argv);
//   rclcpp::spin(std::make_shared<MinimalSubscriber2>());
//   rclcpp::shutdown();
//   return 0;
// }
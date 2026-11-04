#include <chrono>
#include <memory>
#include "std_msgs/msg/string.hpp"
#include "rclcpp/rclcpp.hpp"

using namespace std::chrono_literals;

class ListenerNode : public rclcpp::Node {
public:
  ListenerNode() : Node("listener") {
    subscription_ = create_subscription<std_msgs::msg::String>(
        "chatter", 10,
        [this](const std_msgs::msg::String & msg) {
          RCLCPP_INFO(get_logger(), "heard: '%s'", msg.data.c_str());
        });
  }
private:
  rclcpp::Subscription<std_msgs::msg::String>::SharedPtr subscription_;
};

int main(int argc, char * argv[]) {
  rclcpp::init(argc, argv);
  rclcpp::spin(std::make_shared<ListenerNode>());
  rclcpp::shutdown();
  return 0;
}

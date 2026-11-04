#include <memory>
#include "rclcpp/rclcpp.hpp"
#include "std_msgs/msg/float64.hpp"
#include "std_msgs/msg/string.hpp"

class SteeringHintNode : public rclcpp::Node {
public:
    SteeringHintNode() : Node("steering_hint_node") {
        //设置deadband
        declare_parameter("deadband", 0.1);
        double deadband = get_parameter("deadband").as_double();
        //创建发布工作者
        publisher_ = create_publisher<std_msgs::msg::String>("steering_hint", 10);
        //创建订阅工作者
        subscription_ = create_subscription<std_msgs::msg::Float64>(
            "target_offset", 10,
            [this, deadband](const std_msgs::msg::Float64::SharedPtr msg) { //[自己的](外来的)
                std::string hint;
                if (msg->data < -deadband) { //指向msg代表变量的数据，拿来与deadband比对
                    hint = "LEFT";
                } else if (msg->data > deadband) {
                    hint = "RIGHT";
                } else {
                    hint = "STRAIGHT";
                }
                std_msgs::msg::String out_msg;
                out_msg.data = hint;
                RCLCPP_INFO(get_logger(), "Offset: %f -> %s", msg->data, hint.c_str()); //记录日志
                publisher_->publish(out_msg); //让发布工作者发布out_msg出去
            });
    }
private:
    rclcpp::Publisher<std_msgs::msg::String>::SharedPtr publisher_;
    rclcpp::Subscription<std_msgs::msg::Float64>::SharedPtr subscription_;
};

int main(int argc, char * argv[]) {
    rclcpp::init(argc, argv);
    rclcpp::spin(std::make_shared<SteeringHintNode>());
    rclcpp::shutdown();
    return 0;
}

#include <chrono>
#include <memory>
#include <vector>
#include "rclcpp/rclcpp.hpp"
#include "std_msgs/msg/float64.hpp"

class TargetOffsetPublisher : public rclcpp::Node {
public:
  TargetOffsetPublisher() : Node("target_offset_publisher") {
    //设置参数并存入变量方便后续处理比对
    declare_parameter("amplitude", 0.8);
    declare_parameter("publish_hz", 2.0);
    double amp = get_parameter("amplitude").as_double();
    double hz = get_parameter("publish_hz").as_double();
    
    offsets_ = {-amp, -amp/2.0, 0.0, amp/2.0, amp};
    index_ = 0;

    publisher_ = create_publisher<std_msgs::msg::Float64>("target_offset", 10);
    
    int ms = static_cast<int>(1000.0 / hz);
    //创建闹钟定时处理信息
    timer_ = create_wall_timer(std::chrono::milliseconds(ms), [this]() {
        std_msgs::msg::Float64 msg;
        msg.data = offsets_[index_]; //储存数组数据
        publisher_->publish(msg); //转到create_publisher创建的发布工作者手上，让其发布msg
        index_ = (index_ + 1) % offsets_.size(); //循环遍历数组
    });
  }

private:
  rclcpp::Publisher<std_msgs::msg::Float64>::SharedPtr publisher_;
  rclcpp::TimerBase::SharedPtr timer_;
  std::vector<double> offsets_;
  size_t index_; //定义无符号变量，只能存非负数
};

int main(int argc, char * argv[]) {
  rclcpp::init(argc, argv);
  rclcpp::spin(std::make_shared<TargetOffsetPublisher>());
  rclcpp::shutdown();
  return 0;
}

#include <chrono>
#include <memory>

#include "rclcpp/rclcpp.hpp"
#include "std_srvs/srv/set_bool.hpp"

class SensorStatusNode : public rclcpp::Node {
public:
  SensorStatusNode() : Node("front_camera_status") {
    timer_ = create_wall_timer(std::chrono::seconds(1), [this]() {
      if(is_verbose_){
        RCLCPP_INFO(get_logger(), "front camera status (simulated): READY,TRUE");
      }
      else{
        RCLCPP_INFO(get_logger(), "front camera status (simulated): READY,FALSE");
      }
    });
    service_ = create_service<std_srvs::srv::SetBool>(
        "toggle_diagnostic",
        [this](
            const std::shared_ptr<std_srvs::srv::SetBool::Request> request,
            std::shared_ptr<std_srvs::srv::SetBool::Response> response) {
	  is_verbose_ = request->data;
          response->success = true;
          response->message = "change";
        });    
  }

private:
  rclcpp::TimerBase::SharedPtr timer_;
  rclcpp::Service<std_srvs::srv::SetBool>::SharedPtr service_;  
  bool is_verbose_ = false;
};

int main(int argc, char * argv[]) {
  rclcpp::init(argc, argv);
  rclcpp::spin(std::make_shared<SensorStatusNode>());
  rclcpp::shutdown();
  return 0;
}

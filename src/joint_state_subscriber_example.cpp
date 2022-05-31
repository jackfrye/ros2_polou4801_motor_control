#include <memory>
#include <chrono>

#include "rclcpp/rclcpp.hpp"
#include "rclcpp/subscription_options.hpp"
#include "std_msgs/msg/string.hpp"
#include "sensor_msgs/msg/joint_state.hpp"

using std::placeholders::_1;

class MinimalSubscriber : public rclcpp::Node
{
  public:
    MinimalSubscriber()
    : Node("effort_test_node")
    {
      subscription_ = this->create_subscription<sensor_msgs::msg::JointState>(
      "joint_states", 1, std::bind(&MinimalSubscriber::topic_callback, this, _1));
    }

  private:
    void topic_callback(const sensor_msgs::msg::JointState::SharedPtr msg) const
    {
      RCLCPP_INFO(this->get_logger(), "%s", msg->name[0].c_str());
      RCLCPP_INFO(this->get_logger(), "%f", msg->position[0]);      
      RCLCPP_INFO(this->get_logger(), "MSG Received");
    }
    rclcpp::Subscription<sensor_msgs::msg::JointState>::SharedPtr subscription_;
};

int main(int argc, char * argv[])
{
  rclcpp::init(argc, argv);
  rclcpp::spin(std::make_shared<MinimalSubscriber>());
  rclcpp::shutdown();
  return 0;
}

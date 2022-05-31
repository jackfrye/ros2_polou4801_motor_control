#include <memory>
#include <string>
#include <vector>

#include "rclcpp/rclcpp.hpp"

#include "std_msgs/msg/float64_multi_array.hpp"

std::shared_ptr<rclcpp::Node> node;

int main(int argc, char * argv[])
{
  rclcpp::init(argc, argv);

  node = std::make_shared<rclcpp::Node>("effort_test_node");

  auto publisher = node->create_publisher<std_msgs::msg::Float64MultiArray>(
    "/effort_controllers/commands", 1);

  RCLCPP_INFO(node->get_logger(), "node created");
  
  using namespace std::chrono_literals;
  
  std_msgs::msg::Float64MultiArray commands;
  commands.data.push_back(1);
  publisher->publish(commands);
  std::this_thread::sleep_for(1s);

/* 
  std_msgs::msg::Float64MultiArray commands2;
  commands2.data.push_back(-1);
  publisher->publish(commands2);
  std::this_thread::sleep_for(2s);


  auto publisher2 = node->create_publisher<std_msgs::msg::Float64MultiArray>(
    "/effort_controllers/commands", 1);
  RCLCPP_INFO(node->get_logger(), "second command");
  std_msgs::msg::Float64MultiArray commands2;
  commands2.data.push_back(-1);
  publisher2->publish(commands2);
  std::this_thread::sleep_for(2s);
*/

  RCLCPP_INFO(node->get_logger(), "program end");
  
  return 0;
}

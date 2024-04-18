#include <chrono>
#include <memory>
#include <functional>
#include <string>
#include <stdlib.h>
#include "rclcpp/rclcpp.hpp"
#include "std_msgs/msg/header.hpp"
#include "geometry_msgs/msg/twist.hpp"
#include "nav_msgs/msg/odometry.hpp"
#include "geometry_msgs/msg/pose.hpp"
#include "geometry_msgs/msg/point.hpp"
#include "std_msgs/msg/bool.hpp"

//#include "std_msgs/Float64.hpp"

using namespace std::chrono_literals;
using std::placeholders::_1;

class MinimalSubscriber : public rclcpp::Node
{
  public:
    MinimalSubscriber()
    : Node("node_subscriber")
    {
      subscriber_ = this->create_subscription<nav_msgs::msg::Odometry>("/a200_0000/platform/odom/filtered", 1, std::bind(&MinimalSubscriber::subscribe_message, this, _1));
    }

  private:
    void subscribe_message(const nav_msgs::msg::Odometry::SharedPtr message) const
    {
      nav_msgs::msg::Odometry_<std::allocator<void> >::_pose_type zmienna = (message->pose);
      //std::array<double, 36> zmienna2 = (zmienna.covariance);
      //std::string zmienna3 = "\nLinear x: " + std::to_string(zmienna2[36]) + "\nLinear y: " + std::to_string(zmienna2[37]) + "\nAngular x: " + std::to_string(zmienna2[41]) + "\nAngular y: " + std::to_string(zmienna2[42]);
      //RCLCPP_INFO(this->get_logger(), zmienna3.c_str());

      geometry_msgs::msg::Point pozycja = zmienna.pose.position;
      std::string zmienna3 = "\nLinear x: " + std::to_string(pozycja.x) + "\nLinear y: " + std::to_string(pozycja.y) + "\nLinear z: " + std::to_string(pozycja.z);
      RCLCPP_INFO(this->get_logger(), zmienna3.c_str());
    }
    rclcpp::Subscription<nav_msgs::msg::Odometry>::SharedPtr subscriber_;
};

int main(int argc, char * argv[])
{
  rclcpp::init(argc, argv);
  rclcpp::spin(std::make_shared<MinimalSubscriber>());
  rclcpp::shutdown();
  return 0;
}


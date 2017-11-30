// Create a ROS C++ package entitled “joy_twist”, with dependencies to roscpp, std_msgs, geometry_msgs, and sensor_msgs with the command “catkin_create_pkg joy_twist roscpp std_msgs geometry_msgs sensor_msgs”.

// In this package create a C++ node entitled joy_twist.cpp that subscribes to a sensor_msgs/Joy joystick topic entitled “/joy” and publishes a geometry_msgs/Twist topic named “/edumip/cmd”. We suggest you use a ROS Timer callback function to publish the Twist messages at 10Hz – see ROS Timer documentation for details.

// Your node should assign joystick axis 1 to twist.linear.x, and joystick axis 0 to twisr.angular.z — BUT YOU CAN CHOOSE A DIFFERENT MAPPING IF YOU LIKE — you may need to change a sign in the assignment so that pushing the joystick forward makes twist.linear.x positive, and pushing the joystick to the right makes the twist.angular.z positive.


#include <ros/ros.h>
#include <geometry_msgs/Twist.h>
#include <sensor_msgs/Joy.h>

class TeleopRobot
{
public:
  TeleopRobot();

private:
  void joyCallback(const sensor_msgs::Joy::ConstPtr& joy);

  ros::NodeHandle nh_;

  int linear_, angular_;
  ros::Publisher vel_pub_;
  ros::Subscriber joy_sub_;

};



TeleopRobot::TeleopRobot():
  //JOYSTICK
  // axis 4 to twist.linear.x
  // axis 3 to twist.angular.z
  linear_(4),
  angular_(3)
{

  nh_.param("axis_linear", linear_, linear_);
  nh_.param("axis_angular", angular_, angular_);

  //PUBLISH:geometry_msgs/Twist topic named “/edumip/cmd”
  // Use ROS Timer callback function to publish the Twist messages at 10Hz
  vel_pub_ = nh_.advertise<geometry_msgs::Twist>("edumip/cmd", 1);

  //SUBSCRIBE: sensor_msgs/Joy joystick topic entitled “/joy”
  joy_sub_ = nh_.subscribe<sensor_msgs::Joy>("joy", 10, &TeleopRobot::joyCallback, this);

}


void TeleopRobot::joyCallback(const sensor_msgs::Joy::ConstPtr& joy)
{
  geometry_msgs::Twist twist;
  //JOYSTICK
  // joystick forward makes twist.linear.x positive
  // joystick right makes the twist.angular.z positive

  twist.angular.z = -joy->axes[angular_];
  twist.linear.x = joy->axes[linear_];
  vel_pub_.publish(twist);
}


int main(int argc, char** argv)
{
  ros::init(argc, argv, "teleop_robot_twist");
  TeleopRobot teleop_robot;

  ros::spin();
}

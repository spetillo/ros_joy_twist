// Create a ROS C++ package entitled “joy_twist”, with dependencies to roscpp, std_msgs, geometry_msgs, and sensor_msgs with the command “catkin_create_pkg joy_twist roscpp std_msgs geometry_msgs sensor_msgs”.

// In this package create a C++ node entitled joy_twist.cpp that subscribes to a sensor_msgs/Joy joystick topic entitled “/joy” and publishes a geometry_msgs/Twist topic named “/edumip/cmd”. We suggest you use a ROS Timer callback function to publish the Twist messages at 10Hz – see ROS Timer documentation for details.

// Your node should assign joystick axis 1 to twist.linear.x, and joystick axis 0 to twisr.angular.z — BUT YOU CAN CHOOSE A DIFFERENT MAPPING IF YOU LIKE — you may need to change a sign in the assignment so that pushing the joystick forward makes twist.linear.x positive, and pushing the joystick to the right makes the twist.angular.z positive.



//SUBSCRIBE: sensor_msgs/Joy joystick topic entitled “/joy”

//PUBLISH:geometry_msgs/Twist topic named “/edumip/cmd”
// Use ROS Timer callback function to publish the Twist messages at 10Hz

//JOYSTICK
// axis 1 to twist.linear.x
// axis 0 to twist.angular.z
// joystick forward makes twist.linear.x positive
// joystick right makes the twist.angular.z positive


#include <ros/ros.h>
#include <geometry_msgs/Twist.h>
#include <sensor_msgs/Joy.h>

//ros::geometry_msgs::Twist "/edumip/cmd";
//ros::sensor_msgs::Joy "/joy";

class TeleopRobot
{
public:
  TeleopRobot();

private:
  void joyCallback(const sensor_msgs::Joy::ConstPtr& joy);

  ros::NodeHandle nh_;

  int linear_, angular_;
  // double l_scale_, a_scale_;
  ros::Publisher vel_pub_;
  ros::Subscriber joy_sub_;

};



TeleopRobot::TeleopRobot():
  linear_(4),
  angular_(3)
{

  nh_.param("axis_linear", linear_, linear_);
  nh_.param("axis_angular", angular_, angular_);
  // nh_.param("scale_angular", a_scale_, a_scale_);
  //nh_.param("scale_linear", l_scale_, l_scale_);


  vel_pub_ = nh_.advertise<geometry_msgs::Twist>("edumip/cmd", 1);


  joy_sub_ = nh_.subscribe<sensor_msgs::Joy>("joy", 10, &TeleopRobot::joyCallback, this);

}


void TeleopRobot::joyCallback(const sensor_msgs::Joy::ConstPtr& joy)
{
  geometry_msgs::Twist twist;
  twist.angular.z = joy->axes[angular_];
  twist.linear.x = joy->axes[linear_];
  vel_pub_.publish(twist);
}


int main(int argc, char** argv)
{
  ros::init(argc, argv, "teleop_robot_twist");
  TeleopRobot teleop_robot;

  ros::spin();
}
///////////////////////////////////////
// geometry_msgs::Twist vel_msg_;

// void joyCallback(const sensor_msgs::Joy::ConstPtr& msg){
//   vel_msg_.angular.z = msg->axes[0];
//   vel_msg_.linear.x = msg->axes[1];
//   ROS_INFO("Got axis values?");
// }

// int main(int argc, char** argv){
//   ros::init(argc, argv, "my_joy_twist");

//   ros::NodeHandle node;

//   ros::Subscriber sub = node.subscribe<sensor_msgs::Joy>("joy", 10, &joyCallback);
  
//   ros::Publisher joy_cmd = node.advertise<geometry_msgs::Twist>("edumip/cmd", 10);

//   ros::Rate rate(10.0);
//   while (node.ok()){

//     // geometry_msgs::Twist vel_msg;
//     // vel_msg.linear.x = axes_[1];
//     // vel_msg.angular.z = axes_[0];
    
//     // vel_msg.angular.z = 4.0 * atan2(transform.getOrigin().y(),
//     //                                 transform.getOrigin().x());
//     // vel_msg.linear.x = 0.5 * sqrt(pow(transform.getOrigin().x(), 2) +
//     //                               pow(transform.getOrigin().y(), 2));
//     joy_cmd.publish(vel_msg_);

//     rate.sleep();
//   }
//   ros::spin();

//   return 0;
// };

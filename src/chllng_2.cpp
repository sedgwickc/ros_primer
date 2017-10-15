#include "ros/ros.h"
#include "std_msgs/Int32.h"

#include <sstream>
#include <string>

/**
 * chllnge_1.cpp: a node that adds a two numbers. One number is entered by the
 * and the other is retrieved from the adder topic
 * Alorithm:
 * 1. subscribe to the adder topic and wait for first number
 * 2. tell user first number
 * 3. ask the user for a second number
 * 4. publish second number to the adder topic
 * 5. exit
 *
 */

int main(int argc, char **argv)
{
  /**
   * The ros::init() function needs to see argc and argv so that it can perform
   * any ROS arguments and name remapping that were provided at the command line.
   * For programmatic remappings you can use a different version of init() which takes
   * remappings directly, but for most command-line programs, passing argc and argv is
   * the easiest way to do it.  The third argument to init() is the name of the node.
   *
   * You must call one of the versions of ros::init() before using any other
   * part of the ROS system.
   */
  ros::init(argc, argv, "chllng_2");

  /**
   * NodeHandle is the main access point to communications with the ROS system.
   * The first NodeHandle constructed will fully initialize this node, and the last
   * NodeHandle destructed will close down the node.
   */
  ros::NodeHandle n;

  /* subscribe to adder topic and wait until second number user wants to add is
   * published */
  std::string topic = "adder";
  std_msgs::Int32ConstPtr num1 = ros::topic::waitForMessage<std_msgs::Int32>(topic);
  //ros::Subscriber sub = n.subscribe("adder", 1000, adderCallback);

  /* 3. ask the user for a second number */
  std_msgs::Int32 num2;
  std::cout<<"The first number is: "<<num1->data<<std::endl;
  std::cout<<"Please enter the second number would like to add: "<<std::endl;
  std::cin>>num2.data;

  /* 4. publish second number to the adder topic */

  /**
   * The advertise() function is how you tell ROS that you want to
   * publish on a given topic name. This invokes a call to the ROS
   * master node, which keeps a registry of who is publishing and who
   * is subscribing. After this advertise() call is made, the master
   * node will notify anyone who is trying to subscribe to this topic name,
   * and they will in turn negotiate a peer-to-peer connection with this
   * node.  advertise() returns a Publisher object which allows you to
   * publish messages on that topic through a call to publish().  Once
   * all copies of the returned Publisher object are destroyed, the topic
   * will be automatically unadvertised.
   *
   * The second parameter to advertise() is the size of the message queue
   * used for publishing messages.  If messages are published more quickly
   * than we can send them, the number here specifies how many messages to
   * buffer up before throwing some away.
   */
  ros::Publisher adder_pub = n.advertise<std_msgs::Int32>("adder", 1000);

  ros::Rate loop_rate(10);

  /**
   * A count of how many messages we have sent. This is used to create
   * a unique string for each message.
   */
  int count = 0;
  while (ros::ok() && count < 10)
  {
    /**
     * This is a message object. You stuff it with data, and then publish it.
     */

    ROS_INFO("publishing <%d>", num2.data);

    /**
     * The publish() function is how you send messages. The parameter
     * is the message object. The type of this object must agree with the type
     * given as a template parameter to the advertise<>() call, as was done
     * in the constructor above.
     */
    adder_pub.publish(num2);

    ros::spinOnce();

    loop_rate.sleep();
    ++count;
  }

  return 0;
}

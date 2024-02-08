
#include <ros/ros.h>
#include "geometry_msgs/Pose.h"

class ViconSpoofer
{
    public:

        ViconSpoofer(ros::NodeHandle *nh)
        {
            viconPublisher = nh->advertise<geometry_msgs::Pose>("/vicon/cf1/cf1", 1);

            ros::Rate rate(100);
            while(ros::ok)
            {
                vicon_msg.position.x = 0.0;
                vicon_msg.position.y = 0.0;
                vicon_msg.position.z = 0.4;

                vicon_msg.orientation.x = 0.0;
                vicon_msg.orientation.y = 0.0;
                vicon_msg.orientation.z = 0.0;
                vicon_msg.orientation.w = 1.0;

                viconPublisher.publish(vicon_msg);
                rate.sleep();
            }
        }

        ros::Publisher viconPublisher;

        geometry_msgs::Pose vicon_msg;

};

int main(int argc, char **argv)
{
    ros::init(argc,argv,"Vicon_Spoofer");
    ros::NodeHandle nh;
    ViconSpoofer VS = ViconSpoofer(&nh);
    ros::spin();
    return 1;
}
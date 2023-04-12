
#include <ros/ros.h>
#include "geometry_msgs/TransformStamped.h"
#include "crazyswarm/Position.h"

class ViconSpoofer
{
    public:

        ViconSpoofer(ros::NodeHandle *nh)
        {
            viconPublisher = nh->advertise<crazyswarm::Position>("/vicon/cf1/cf1", 1);

            ros::Rate rate(100);
            while(ros::ok)
            {
                vicon_msg.x = 0.0;
                vicon_msg.y = 0.0;
                vicon_msg.z = 0.4;


                viconPublisher.publish(vicon_msg);
                rate.sleep();
            }
        }

        ros::Publisher viconPublisher;

        crazyswarm::Position vicon_msg;

};

int main(int argc, char **argv)
{
    ros::init(argc,argv,"Vicon_Spoofer");
    ros::NodeHandle nh;
    ViconSpoofer VS = ViconSpoofer(&nh);
    ros::spin();
    return 1;
}
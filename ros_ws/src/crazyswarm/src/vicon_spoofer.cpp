
#include <ros/ros.h>
#include "geometry_msgs/TransformStamped.h"
#include "crazyswarm/GTC_Cmd.h"

class ViconSpoofer
{
    public:

        ViconSpoofer(ros::NodeHandle *nh)
        {
            viconPublisher = nh->advertise<crazyswarm::GTC_Cmd>("/cmd_GTC", 1);

            ros::Rate rate(4);
            while(ros::ok)
            {
                vicon_msg.cmd_vals.x = 0.1;
                vicon_msg.cmd_vals.y = 0.2;
                vicon_msg.cmd_vals.z = 0.3;


                viconPublisher.publish(vicon_msg);
                rate.sleep();
            }
        }

        ros::Publisher viconPublisher;

        crazyswarm::GTC_Cmd vicon_msg;

};

int main(int argc, char **argv)
{
    ros::init(argc,argv,"Vicon_Spoofer");
    ros::NodeHandle nh;
    ViconSpoofer VS = ViconSpoofer(&nh);
    ros::spin();
    return 1;
}
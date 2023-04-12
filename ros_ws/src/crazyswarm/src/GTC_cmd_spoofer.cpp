
#include <ros/ros.h>
#include "geometry_msgs/TransformStamped.h"
#include "crazyswarm/GTC_Cmd.h"

class GTC_CMD_Spoofer
{
    public:

        GTC_CMD_Spoofer(ros::NodeHandle *nh)
        {
            GTC_CMD_Publisher = nh->advertise<crazyswarm::GTC_Cmd>("/cmd_GTC", 1);

            ros::Rate rate(1);
            while(ros::ok)
            {
                CMD_msg.cmd_type = 1;
                CMD_msg.cmd_vals.x = 1.1;
                CMD_msg.cmd_vals.y = 2.2;
                CMD_msg.cmd_vals.z = 3.3;
                CMD_msg.cmd_flag = 1.0;
                CMD_msg.cmd_rx = true;



                GTC_CMD_Publisher.publish(CMD_msg);
                rate.sleep();
            }
        }

        ros::Publisher GTC_CMD_Publisher;

        crazyswarm::GTC_Cmd CMD_msg;

};

int main(int argc, char **argv)
{
    ros::init(argc,argv,"GTC_CMD_Spoofer");
    ros::NodeHandle nh;
    GTC_CMD_Spoofer GTC_Spoofer = GTC_CMD_Spoofer(&nh);
    ros::spin();
    return 1;
}
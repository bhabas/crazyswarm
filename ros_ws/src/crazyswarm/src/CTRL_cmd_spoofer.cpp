
#include <ros/ros.h>
#include "geometry_msgs/TransformStamped.h"
#include "crazyswarm/CTRL_Cmd.h"

class CTRL_CMD_Spoofer
{
    public:

        CTRL_CMD_Spoofer(ros::NodeHandle *nh)
        {
            CTRL_CMD_Publisher = nh->advertise<crazyswarm::CTRL_Cmd>("/SAR_DC/CMD_Output_Topic", 1);

            ros::Rate rate(1);
            while(ros::ok)
            {
                CMD_msg.cmd_type = 5;
                CMD_msg.cmd_vals.x = 0;
                CMD_msg.cmd_vals.y = 2.2;
                CMD_msg.cmd_vals.z = 3.3;
                CMD_msg.cmd_flag = 1.0;
                CMD_msg.cmd_rx = true;



                CTRL_CMD_Publisher.publish(CMD_msg);
                rate.sleep();
            }
        }

        ros::Publisher CTRL_CMD_Publisher;

        crazyswarm::CTRL_Cmd CMD_msg;

};

int main(int argc, char **argv)
{
    ros::init(argc,argv,"CTRL_CMD_Spoofer");
    ros::NodeHandle nh;
    CTRL_CMD_Spoofer CTRL_Spoofer = CTRL_CMD_Spoofer(&nh);
    ros::spin();
    return 1;
}
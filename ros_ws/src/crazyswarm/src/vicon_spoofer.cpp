#include <ros/ros.h>
#include "geometry_msgs/Pose.h"
#include <crazyswarm/SetPose.h> // Adjust to your package and service
#include <tf/tf.h>
#include <random>

#define DEG2RAD M_PI / 180.0
#define RAD2DEG 180.0 / M_PI

class ViconSpoofer
{
public:
    ViconSpoofer(ros::NodeHandle *nh) : nh_(*nh),
                                        gen(rd()),
                                        dis_position(0.0, 0.001), // Standard deviation for position, adjust as needed
                                        dis_orientation(0.0, 0.1) // Standard deviation for orientation, adjust as needed
    {
        viconPublisher = nh_.advertise<geometry_msgs::Pose>("/vicon/cf1/cf1", 1);
        service = nh_.advertiseService("ViconSpooder/SetPose", &ViconSpoofer::setPoseCallback, this);

        ros::Rate rate(100);
        while(ros::ok())
        {
            applyNoise();
            viconPublisher.publish(vicon_msg);
            ros::spinOnce();
            rate.sleep();
        }
    }

    bool setPoseCallback(crazyswarm::SetPose::Request &req,
                         crazyswarm::SetPose::Response &res)
    {
        // Convert degrees to radians for the Euler angles
        double roll_rad = req.roll * DEG2RAD;
        double pitch_rad = req.pitch * DEG2RAD;
        double yaw_rad = req.yaw * DEG2RAD;

        // Store original (bias) values
        bias_position_x = req.x;
        bias_position_y = req.y;
        bias_position_z = req.z;
        bias_orientation = tf::createQuaternionFromRPY(roll_rad, pitch_rad, yaw_rad);

        res.success = true;
        res.message = "Pose bias updated successfully.";
        return true;
    }

private:
    void applyNoise()
    {
        // Apply Gaussian noise to the bias values each cycle
        vicon_msg.position.x = bias_position_x + dis_position(gen);
        vicon_msg.position.y = bias_position_y + dis_position(gen);
        vicon_msg.position.z = bias_position_z + dis_position(gen);

        // For orientation, add noise to the Euler angles and then convert to quaternion
        double roll, pitch, yaw;
        tf::Matrix3x3(bias_orientation).getRPY(roll, pitch, yaw);
        roll += dis_orientation(gen) * DEG2RAD;
        pitch += dis_orientation(gen) * DEG2RAD;
        yaw += dis_orientation(gen) * DEG2RAD;
        tf::Quaternion q_noise = tf::createQuaternionFromRPY(roll, pitch, yaw);
        tf::quaternionTFToMsg(q_noise, vicon_msg.orientation);
    }

    ros::NodeHandle nh_;
    ros::Publisher viconPublisher;
    ros::ServiceServer service;
    geometry_msgs::Pose vicon_msg;
    std::random_device rd;
    std::mt19937 gen;
    std::normal_distribution<> dis_position;
    std::normal_distribution<> dis_orientation;

    // Bias values
    double bias_position_x = 0.0, bias_position_y = 0.0, bias_position_z = 0.4;
    tf::Quaternion bias_orientation = tf::createQuaternionFromRPY(0.0, 0.0, 0.0);
};

int main(int argc, char **argv)
{
    ros::init(argc, argv, "Vicon_Spoofer");
    ros::NodeHandle nh;
    ViconSpoofer VS(&nh);
    return 0;
}

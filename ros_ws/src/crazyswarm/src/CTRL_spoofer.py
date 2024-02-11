#!/usr/bin/env python

import rospy
from crazyswarm.msg import CTRL_Cmd

def talker():
    # Initialize node
    rospy.init_node('CTRL_cmd_spoofer', anonymous=True)
    # Create publisher with topic name and message type
    pub = rospy.Publisher('/CF_DC/Cmd_CF_DC', CTRL_Cmd, queue_size=10)
    # Set the loop rate (in Hz)
    rate = rospy.Rate(1) # 10 Hz
    # Create a message object
    msg = CTRL_Cmd()

    msg.cmd_type = 5
    msg.cmd_vals.x = 0
    msg.cmd_vals.y = 0
    msg.cmd_vals.z = 0
    msg.cmd_flag = 0.0
    msg.cmd_rx = False

    while not rospy.is_shutdown():
        # Update the message header timestamp
        msg.header.stamp = rospy.Time.now()
        # Publish the message
        pub.publish(msg)
        # Sleep for the remaining time in the loop to achieve the desired loop rate
        rate.sleep()

if __name__ == '__main__':
    try:
        talker()
    except rospy.ROSInterruptException:
        pass

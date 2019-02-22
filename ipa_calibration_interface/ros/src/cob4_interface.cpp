/****************************************************************
 *
 * Copyright (c) 2017
 *
 * Fraunhofer Institute for Manufacturing Engineering
 * and Automation (IPA)
 *
 * +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
 *
 * Project name: ipa_calibration
 * ROS stack name: ipa_calibration
 * ROS package name: ipa_calibration_interface
 *
 * +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
 *
 * Author: Marc Riedlinger, email: m.riedlinger@live.de
 *
 * Date of creation: September 2017
 *
 * +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 *     * Redistributions of source code must retain the above copyright
 *       notice, this list of conditions and the following disclaimer.
 *     * Redistributions in binary form must reproduce the above copyright
 *       notice, this list of conditions and the following disclaimer in the
 *       documentation and/or other materials provided with the distribution.
 *     * Neither the name of the Fraunhofer Institute for Manufacturing
 *       Engineering and Automation (IPA) nor the names of its
 *       contributors may be used to endorse or promote products derived from
 *       this software without specific prior written permission.
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License LGPL as
 * published by the Free Software Foundation, either version 3 of the
 * License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Lesser General Public License LGPL for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License LGPL along with this program.
 * If not, see <http://www.gnu.org/licenses/>.
 *
 ****************************************************************/

#include <ipa_calibration_interface/cob4_interface.h>
#include <trajectory_msgs/JointTrajectoryPoint.h>
#include <trajectory_msgs/JointTrajectory.h>
#include <control_msgs/FollowJointTrajectoryAction.h>
#include <control_msgs/FollowJointTrajectoryGoal.h>
#include <actionlib/client/simple_action_client.h>

Cob4Interface::Cob4Interface(ros::NodeHandle* nh, CalibrationType* calib_type, CalibrationMarker* calib_marker, bool do_arm_calibration, bool load_data) :
				IPAInterface(nh, calib_type, calib_marker, do_arm_calibration, load_data)
{
	std::cout << "\n========== Cob4Interface Parameters ==========\n";

	/*node_handle_.param<std::string>("camera_joint_controller_command", camera_joint_controller_command_, "");
	std::cout << "camera_joint_controller_command: " << camera_joint_controller_command_ << std::endl;
	camera_joint_controller_ = node_handle_.advertise<std_msgs::Float64MultiArray>(camera_joint_controller_command_, 1, false);

	node_handle_.param<std::string>("camera_joint_state_topic", camera_joint_state_topic_, "");
	std::cout << "camera_joint_state_topic: " << camera_joint_state_topic_ << std::endl;
	camera_state_ = node_handle_.subscribe<sensor_msgs::JointState>(camera_joint_state_topic_, 0, &Cob4Interface::cameraStateCallback, this);*/

	sensorring_static_state_.push_back(0.f);

	if ( arm_calibration_ )
	{
		node_handle_.param<std::string>("arm_left_command", arm_left_command_, "");
		std::cout << "arm_left_command: " << arm_left_command_ << std::endl;
		arm_left_controller_ = node_handle_.advertise<trajectory_msgs::JointTrajectory>(arm_left_command_, 1, false);

		node_handle_.param<std::string>("arm_left_state_topic", arm_left_state_topic_, "");
		std::cout << "arm_left_state_topic: " << arm_left_state_topic_ << std::endl;
		arm_left_state_ = node_handle_.subscribe<sensor_msgs::JointState>(arm_left_state_topic_, 0, &Cob4Interface::armLeftStateCallback, this);

		node_handle_.param<std::string>("arm_right_command", arm_right_command_, "");
		std::cout << "arm_right_command: " << arm_right_command_ << std::endl;
		arm_right_controller_ = node_handle_.advertise<trajectory_msgs::JointTrajectory>(arm_right_command_, 1, false);

		node_handle_.param<std::string>("arm_right_state_topic", arm_right_state_topic_, "");
		std::cout << "arm_right_state_topic: " << arm_right_state_topic_ << std::endl;
		arm_right_state_ = node_handle_.subscribe<sensor_msgs::JointState>(arm_right_state_topic_, 0, &Cob4Interface::armRightStateCallback, this);
	}
	else
	{
		node_handle_.param<std::string>("base_controller_topic_name", base_velocity_command_, "");
		std::cout << "base_velocity_command: " << base_velocity_command_ << std::endl;
		base_velocity_controller_ = node_handle_.advertise<geometry_msgs::Twist>(base_velocity_command_, 1, false);
	}

	// /arm_left/joint_group_position_controller/command
	// /arm_right/joint_group_position_controller/command
	// /base/velocity_smoother/command

	ROS_INFO("Cob4Interface::Cob4Interface - Cob4Interface initialized.");
}

Cob4Interface::~Cob4Interface()
{
}

// Callbacks
void Cob4Interface::cameraStateCallback(const sensor_msgs::JointState::ConstPtr& msg)
{

}

void Cob4Interface::armLeftStateCallback(const sensor_msgs::JointState::ConstPtr& msg)
{

}

void Cob4Interface::armRightStateCallback(const sensor_msgs::JointState::ConstPtr& msg)
{

}
// End callbacks

void Cob4Interface::assignNewRobotVelocity(geometry_msgs::Twist new_velocity)
{
	base_velocity_controller_.publish(new_velocity);
}

void Cob4Interface::assignNewCameraAngles(const std::string &camera_name, std_msgs::Float64MultiArray new_camera_config)
{

}

std::vector<double>* Cob4Interface::getCurrentCameraState(const std::string &camera_name)
{
	if ( camera_name.compare("sensorring_dummy") == 0 )
		return &sensorring_static_state_;

	return 0;
}

void Cob4Interface::assignNewArmJoints(const std::string &arm_name, std_msgs::Float64MultiArray new_arm_config)
{

}

std::vector<double>* Cob4Interface::getCurrentArmState(const std::string &arm_name)
{
	return 0;
}

std::string Cob4Interface::getRobotName()
{
	return "cob-4-7";
}








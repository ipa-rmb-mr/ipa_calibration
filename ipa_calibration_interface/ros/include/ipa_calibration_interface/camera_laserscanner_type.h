/****************************************************************
 *
 * Copyright (c) 2018
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
 * Date of creation: June 2018
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

#ifndef CAMERA_LASERSCANNER_TYPE_H_
#define CAMERA_LASERSCANNER_TYPE_H_


#include <ipa_calibration_interface/calibration_type.h>
#include <ipa_calibration_interface/pose_definition.h>
#include <opencv2/opencv.hpp>


#define REF_FRAME_HISTORY_SIZE 20 // 20 entries used to build the moving average upon


class CameraLaserscannerType : public CalibrationType
{

public:

	CameraLaserscannerType();
	~CameraLaserscannerType();
	void initialize(ros::NodeHandle* nh, IPAInterface* calib_interface);

	bool moveRobot(int config_index);
	std::string getString();


protected:

	bool moveCameras(int config_index);
    unsigned short moveBase(const pose_definition::RobotConfiguration &base_configuration);

    bool isReferenceFrameValid(cv::Mat &T, unsigned short& error_code);  // returns wether reference frame is valid -> if so, it is save to move the robot base, otherwise stop!
    bool divergenceDetectedRotation(double error_phi, bool start_value);  // rotation controller diverges!
    bool divergenceDetectedLocation(double error_x, double error_y, bool start_value);  // location controller diverges!
    void turnOffBaseMotion();  // set angular and linear speed to 0
	bool transformControllerErrorPos(const cv::Mat &T_base_to_ref, double &error_x, double &error_y);  // transform position error to controller_frame
	bool transformControllerErrorRot(double &error_phi);  // transform rotation error to controller_frame

    double ref_frame_history_[REF_FRAME_HISTORY_SIZE]; // History of base_frame to reference_frame squared lengths, used to get average squared length. Holds last <REF_FRAME_HISTORY_SIZE> measurements.
    double max_ref_frame_distance_;

    std::vector<pose_definition::RobotConfiguration> base_configurations_;  // wished base configurations used for calibration

	std::string base_frame_;		// robot base moves until this frame is correctly aligned relative to the reference_frame
	std::string reference_frame_;	// robot base will be moved relative to this frame (base_configurations must be typed relative to this frame)
	std::string controller_frame_;	// controller error will be transformed in this frame before being applied to the motors


private:

    double last_ref_history_update_;  // used to update the ref_frame_history_ array cyclically and not upon every call of isReferenceFrameValid()
    int ref_history_index_; // Current index of history building

    double start_error_phi_;	// Used for divergence detection
    double start_error_x_;	// Used for divergence detection
    double start_error_y_;	// Used for divergence detection

	int mapped_base_index_;  // mapped index that accesses the correct vector element of the base_configurations_ vector
	int mapped_camera_index_;  // mapped index that accesses the correct vector element of the currently moved camera
	int current_camera_counter_;  // used to determine which camera to move
	bool cameras_done_;  // set when all cameras have iterated through all their configs. used to determine when to move robot's base (every time cameras are done)


};


#endif /* CAMERA_LASERSCANNER_TYPE_H_ */

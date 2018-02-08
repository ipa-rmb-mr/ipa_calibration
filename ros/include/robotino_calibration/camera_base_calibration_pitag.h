/****************************************************************
 *
 * Copyright (c) 2015
 *
 * Fraunhofer Institute for Manufacturing Engineering
 * and Automation (IPA)
 *
 * +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
 *
 * Project name: squirrel
 * ROS stack name: squirrel_calibration
 * ROS package name: robotino_calibration
 *
 * +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
 *
 * Author: Richard Bormann, email:richard.bormann@ipa.fhg.de
 *
 * Date of creation: August 2016
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

#ifndef __CAMERA_BASE_CALIBRATION_PITAG_H__
#define __CAMERA_BASE_CALIBRATION_PITAG_H__


#include <robotino_calibration/camera_base_calibration_marker.h>


class CameraBaseCalibrationPiTag : public CameraBaseCalibrationMarker
{
public:

    CameraBaseCalibrationPiTag(ros::NodeHandle nh, CalibrationInterface* interface);
    ~CameraBaseCalibrationPiTag();

    // starts the calibration between camera and base including data acquisition
    bool calibrateCameraToBase(const bool load_data);

    // load/save calibration data from/to file
    // not needed anymore
    //bool saveCalibration();
    //bool loadCalibration();
    //void getCalibration(cv::Mat& T_base_to_torso_lower, cv::Mat& T_torso_upper_to_camera);


protected:

    // acquires images automatically from all set up robot configurations and detects the pitags
    // @param load_images loads calibration images and transformations from hard disk if set to true (transformations are stored automatically)
    // retrieves all relevant transformations
    bool acquireCalibrationData(const bool load_data, std::vector<cv::Mat>& T_gapfirst_to_marker_vector,
                                std::vector< std::vector<cv::Mat> >& T_between_gaps_vector, std::vector<cv::Mat>& T_gaplast_to_marker_vector);

    ros::ServiceClient pitag_client_;
    std::string marker_frame_base_name_;
    std::string get_fiducials_topic_;
};

#endif // __CAMERA_BASE_CALIBRATION_PITAG_H__

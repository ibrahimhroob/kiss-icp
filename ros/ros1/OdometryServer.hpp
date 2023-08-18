// MIT License
//
// Copyright (c) 2022 Ignacio Vizzo, Tiziano Guadagnino, Benedikt Mersch, Cyrill
// Stachniss.
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.
#pragma once

// KISS-ICP
#include "kiss_icp/pipeline/KissICP.hpp"

// ROS
#include "nav_msgs/Path.h"
#include "ros/ros.h"
#include "sensor_msgs/PointCloud2.h"
#include "tf2_ros/transform_broadcaster.h"

namespace kiss_icp_ros {

class OdometryServer {
public:
    /// OdometryServer constructor
    OdometryServer(const ros::NodeHandle &nh, const ros::NodeHandle &pnh);

private:
    /// Register frame
    void RegisterFrame(const sensor_msgs::PointCloud2::ConstPtr &msg);

    void EstimateFrame(const sensor_msgs::PointCloud2::ConstPtr &msg);

    void PublishMap();

    /// Ros node stuff
    ros::NodeHandle nh_;
    ros::NodeHandle pnh_;
    int queue_size_{1};

    /// Tools for broadcasting TFs.
    tf2_ros::TransformBroadcaster tf_broadcaster_;
    bool publish_odom_tf_;
    bool publish_alias_tf_;

    /// Data subscribers.
    ros::Subscriber pointcloud_raw_sub_;
    ros::Subscriber pointcloud_filtered_sub_;

    /// Data publishers.
    ros::Publisher odom_publisher_;
    ros::Publisher traj_publisher_;
    nav_msgs::Path path_msg_;
    ros::Publisher frame_publisher_estimated_;
    ros::Publisher frame_publisher_registered_;
    ros::Publisher kpoints_publisher_;
    ros::Publisher map_publisher_;

    /// KISS-ICP
    kiss_icp::pipeline::KissICP odometry_;
    kiss_icp::pipeline::KISSConfig config_;

    /// Global/map coordinate frame.
    std::string odom_frame_{"odom"};
    std::string child_frame_{"base_link"};
    std::string map_pth_{""};

    std_msgs::Header raw_frame_header_;
};

}  // namespace kiss_icp_ros

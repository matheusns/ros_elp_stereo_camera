#include "include/elp_camera.hpp"
#include <iostream>
#include <unistd.h>


void testCall(const cv::Mat& src)
{
    cv::cvtColor(src, src, CV_RGB2BGR);
    ROS_INFO("Test Call");
    cv::imshow("test", src);
    char key = cv::waitKey(1);
}

int main(int argc, char **argv)
{
    ros::init(argc, argv, "elp_camera_node");
    elp::ElpCamera camera;
    try
    {
        camera.setupCallback( std::bind(testCall, std::placeholders::_1) );
        camera.startStreaming();
    }
    catch (elp::ElpCameraException& e)
    {
        ROS_INFO_STREAM( e.what() );
    }
    ros::spin();
}
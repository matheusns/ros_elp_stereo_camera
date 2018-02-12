#include "include/elp_camera.hpp"
#include <iostream>

int main(int argc, char **argv)
{
    ros::init(argc, argv, "elp_camera_node");
    elp::ElpCamera camera;
    ros::spin();
}
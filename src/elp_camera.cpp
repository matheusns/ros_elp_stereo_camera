#include "include/elp_camera.hpp"

namespace elp
{
ElpCamera::ElpCamera()
    : callback_(nullptr)
    , image_width_(1280)
    , image_height_(720)
    , is_streaming_(false)
    , img_aqt_th_(nullptr)
    , nh_("~")
{
    
} 

ElpCamera::~ElpCamera()
{
    
}

void ElpCamera::setupCallback(const GrabCallback frame_callback)
{
    if (frame_callback != nullptr)
    {
            callback_ = frame_callback;
    }
    else throw ElpCameraException("Null callback, please use the setupCallback funtion before start.");
}

void ElpCamera::startStreaming()
{
    if (callback_ != nullptr)
    {
        if (!is_streaming_)
        {
            img_aqt_th_ = new std::thread(&ElpCamera::imageAcquisition, this);
            is_streaming_ = true;
        }
    }
    else throw ElpCameraException("Null callback, please use the setupCallback funtion before start the streaming.");
}

void ElpCamera::stopStreaming() 
{
    if (is_streaming_)
    {
        is_streaming_ = false;  
    }
}

void ElpCamera::imageAcquisition()
{
    cv::VideoCapture right_camera(0);
    cv::VideoCapture left_camera(2);

    right_camera.set(CV_CAP_PROP_FRAME_WIDTH, image_width_);
    left_camera.set(CV_CAP_PROP_FRAME_WIDTH, image_width_);

    right_camera.set(CV_CAP_PROP_FRAME_HEIGHT, image_height_);
    left_camera.set(CV_CAP_PROP_FRAME_HEIGHT, image_height_);

    right_camera.set( CV_CAP_PROP_FOURCC ,CV_FOURCC('M', 'J', 'P', 'G') );
    left_camera.set( CV_CAP_PROP_FOURCC ,CV_FOURCC('M', 'J', 'P', 'G') );

    
    is_streaming_ = false;
}
} // elp namespace 